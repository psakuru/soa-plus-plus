/**
 * @file ImageRegister.h
 * @author  Sacco Cosimo <cosimosacco@gmail.com>, Silvestri Davide <davidesil.web@gmail.com>
 *
 * @section LICENSE
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "../ObjectInterfaces/SingletonObject/SingletonObject.h"
#include "../ServiceOrientedArchitecture/Service/Skeleton/RegistrablePoolableCyclicCallableSkeleton/RegistrablePoolableCyclicCallableSkeleton.h"
#include "../SerializableObjects/SerializationStrategies/StringSerializationStrategy/StringSerializationStrategy.h"
#include <string>
#include <list>
#include <iostream>
using namespace std;

class ImageRegister: public RegistrablePoolableCyclicCallableSkeleton {
private:
	boost::shared_mutex mutex;
	void doService() {
		string* requestedOperation = ((string*) (inputParameters.front())->getValue());
		inputParameters.pop_front();
		if (requestedOperation->compare("storeImage") == 0)
			storeImage();
		if (requestedOperation->compare("getImage") == 0)
			getImage();
		if (requestedOperation->compare("getList") == 0)
			getList();
		delete requestedOperation;
		inputParameters.clear();
	}
	void storeImage() 
	{
		boost::unique_lock<boost::shared_mutex> writersLock(mutex);
		list<string>* imageList = SingletonObject< list <string> >::getInstance(); // Istanza singleton.
		SerializableObjectList::iterator i = inputParameters.begin();
		string* entry = (string*)(*i)->getValue();
		string name = *entry;
		delete entry;
		i++;
		ByteArray* pb = (ByteArray*) (*i)->getValue();
		ofstream outfile(name.c_str(), ofstream::binary | ofstream::out);
		outfile.write((char*) (pb->getPointer()), pb->getLength());
		outfile.close();
		delete pb;
		if((find_if(imageList->begin(), imageList->end(), name.compare)!=imageList->end())
			imageList->push_front(name);
	}
	void getImage() 
	{
		boost::shared_lock<boost::shared_mutex> readersLock(mutex);
		list<string>* imageList = SingletonObject< list <string> >::getInstance(); // Istanza singleton.
		SerializableObjectList::iterator i = inputParameters.begin();
		string* entry = (string*)(*i)->getValue();
		string name = *entry;
		delete entry;
		if((find_if(imageList->begin(),imageList->end(), name.compare)!=imageList->end())
		{
			//TODO ECCEZIONE - il file non esiste o comunque non è stato registrato.
		}
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
		outputParameters.push_back(objectToBeSent); 
	}
	void getList()
	{
		boost::shared_lock<boost::shared_mutex> readersLock(mutex);
		list<string>* imageList = SingletonObject< list <string> >::getInstance(); // Istanza singleton.
		string app;
		list<string>::iterator i = imageList->begin();
		for(; i != imageList->end(); i++)
        {
			app.append("[");app.append(*i);app.append("]\n");
        }
		string* listToBeReturned = new string(app);
        outputParameters.push_back(new String(listToBeReturned, false));
	}
public:
	ImageRegister() : Skeleton("ImageRegister"), RegistrablePoolableCyclicCallableSkeleton("ImageRegister") {
	}
	void receiveParameters()
	{
		SerializableObjectList::size_type* incomingParametersSizePointer =
				((SerializableObjectList::size_type*) socket->receiveMessage(
						sizeof(SerializableObjectList::size_type)));
		SerializableObjectList::size_type incomingParametersSize =
				*incomingParametersSizePointer;
		free(incomingParametersSizePointer);
		if(incomingParametersSize > 3)
		{
			//TODO LANCIA ECCEZIONE!
		}
		SerializableObjectList* incomingParameters = new SerializableObjectList; // Comando
		inputParameters.push_back(new String);
		inputParameters.push_back(new String); // Nome dell' immagine (GetImage, StoreImage) o lista da ritornare (GetList).
		if(incomingParametersSize > 2) // Immagini in GetImage, StoreImage.
		{
			inputParameters.push_back(new RawByteBuffer);
		}
		for (unsigned int i = 0; i < incomingParametersSize; i++) 
		{
			incomingParameters->push_back(receiveParameter());
		}
		SerializableObjectList::iterator i = inputParameters.begin();
		SerializableObjectList::iterator j = incomingParameters->begin();
		while (i != inputParameters.end()) 
		{
			*(*i) = *(*j);  // In caso di type-mismatch lancia un' eccezione.
			i++;
			j++;
		}
		delete incomingParameters;
	}
	~ImageRegister() {
		SingletonObject< list<string> >::destroyInstance();  // Elimina l' istanza Singleton.
	}
};
