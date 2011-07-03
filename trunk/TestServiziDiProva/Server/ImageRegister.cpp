#include "../../ObjectInterfaces/SingletonObject/SingletonObject.h"
#include "Utilities/ExtensibleMap/MonitoredExtensibleMap/RRFIFOMonitoredExtensibleMap/RRFIFOMonitoredExtensibleMap.h"
#include "../Service/Skeleton/RegistrablePoolableCyclicCallableSkeleton/RegistrablePoolableCyclicCallableSkeleton.h"
#include "../../SerializableObjects/SerializationStrategies/StringSerializationStrategy/StringSerializationStrategy.h"
#include <string>
#include <list>
using namespace std;

class ImageRegister: public RegistrablePoolableCyclicCallableSkeleton {
private:
	List<string> imageList;
protected:
	void doService() {
		string requestedOperation(
				*((string*) (inputParameters.front())->getValue()));
		inputParameters.pop_front();
		if (requestedOperation.compare("storeImage") == 0)
			storeImage();
		if (requestedOperation.compare("getImage") == 0)
			getImage();
		if (requestedOperation.compare("getList") == 0)
			getMap();
		//Se nessuno di questi if si attiva il registro non fa niente, alla fine risponde lista vuota e tutti contenti
		inputParameters.clear();
	}
	void storeImage() {
		SerializableObjectList::iterator i = inputParameters.begin();
		i++;//NON VA FATTO COS“ ANCHE NEL REGISTER??
		SerializableObject* d = (*i);
		string name = (String)(d->getValue());
		//TODO ECCEZIONE IN CASO DI IMMAGINE GIA ESISTENTE + CONTROLLI SULL'IMMAGINE?? (jpg ecc..)
		i++;
		SerializableObject* r = (*i);
		ByteArray* pb = (ByteArray*) (r->getValue());
		//TODO ECCEZIONI!!
		ofstream outfile(name3, ofstream::binary | ofstream::out);
		outfile.write((char*) (pb->getPointer()), pb->getLength());
		outfile.close();
		delete pb;
		//MODO PIU' EFFICIENTE? TIPO UNA HASHMAP?
		imageList.push_front(name);
		//inputParameters.clear();//LO FA GIA?
	}
	void getImage() {
		SerializableObjectList::iterator i = inputParameters.begin();
		i++;//NON VA FATTO COS“ ANCHE NEL REGISTER??
		SerializableObject* d = (*i);
		string name = (String)(d->getValue());
		//TODO ECCEZIONE IN CASO DI IMMAGINE NON ESISTENTE
		//MODO PIU' EFFICIENTE? TIPO UNA HASHMAP?
		imageList.erase(name);
		//inputParameters.clear();
		char * memblock;
		uint64_t size = 0;
		ifstream file(name, ios::in | ios::binary | ios::ate);
		if (file.is_open()) {
			size = (int) file.tellg();
			memblock = (char*) malloc(size);
			file.seekg(0, ios::beg);
			file.read(memblock, size);
			file.close();

		} else {
			//TODO ECCEZIONE - fare un try chatch con un robo che comunque faccia a remove del file
		}
		ByteArray* fileBytes = new ByteArray((void*) memblock, size);
		free(memblock);
		remove(name);
		RawByteBuffer* objectToBeSent = new RawByteBuffer(fileBytes, false);
		//  BadRequest* badRequest = new BadRequest();
		outputParameters.push_back(objectToBeSent); //Tanto poi ci pensa la lista boost a fare la delete!
		//  outputParameters.push_back(badRequest);
	}
	void getList(){
		string app;
		for(int i=0;!imageList.empty();i++){
			app.append((string)imageList.push_front());
			app.append('\n');
		}
		String* listToBeReturned  = new String(app);
		outputParameters.push_back(listToBeReturned); //Tanto poi ci pensa la lista boost a fare la delete!
	}
public:
	ImageRegister() :
		Skeleton("ImageRegister"),
				RegistrablePoolableCyclicCallableSkeleton("ImageRegister") {
	}
	void receiveParameters() //throws SocketException, IncompatibleTypes
	{
		SerializableObjectList::size_type* incomingParametersSizePointer =
				((SerializableObjectList::size_type*) socket->receiveMessage(
						sizeof(SerializableObjectList::size_type)));
		SerializableObjectList::size_type incomingParametersSize =
				*incomingParametersSizePointer;
		free(incomingParametersSizePointer);
		//PERCHE' SERVE QUESTA LISTA DI APPOGGIO??
		SerializableObjectList* incomingParameters = new SerializableObjectList;
		inputParameters.push_back(new String); //per l' operazione
		for (unsigned int i = 0; i < (incomingParametersSize - 1); i++) {
			inputParameters.push_back(new String);
		}
		for (unsigned int i = 0; i < incomingParametersSize; i++) {
			incomingParameters->push_back(receiveParameter());
		}
		SerializableObjectList::iterator i = inputParameters.begin();
		SerializableObjectList::iterator j = incomingParameters->begin();
		while (i != inputParameters.end()) {
			*(*i) = *(*j);
			i++;
			j++;
		}
		delete incomingParameters;
	}
	~ImageRegister() {//Elimina l' istanza Singleton
		imageList.clear();//chiama tutti i distruttori
		imageList = NULL;
	}
};
