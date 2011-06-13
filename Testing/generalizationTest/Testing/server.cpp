#include <iostream>
#include <fstream>
#include <list>
#include <exception>
#include "../TcpIpSocket/TcpIpPassiveSocket.h"
#include "../SerializableObjects/SerializableObject.h"
#include "../SerializableObjects/DeserializationStrategies/SerializableObjectBuilder.h"
#include "../SerializableObjects/DeserializationStrategies/TerminalSerializableObjectBuilder.h"
#include "../SerializableObjects/Utilities/ByteArray/ByteArray.h"
#include "../SerializableObjects/SerializationStrategies/RawByteBufferSerializationStrategy/RawByteBufferSerializationStrategy.h"
#include "../SerializableObjects/SerializationStrategies/IntegerSerializationStrategy/IntegerSerializationStrategy.h"
#include "../SerializableObjects/SerializationStrategies/RealSerializationStrategy/RealSerializationStrategy.h"
#include "../SerializableObjects/SerializationStrategies/StringSerializationStrategy/StringSerializationStrategy.h"
#include "../SerializableObjects/SerializationStrategies/SignalSerializationStrategy/SignalSerializationStrategy.h"
#include "../SerializableObjects/DeserializationStrategies/SignalBuilder.h"
#include "../SerializableObjects/SerializationStrategies/SignalSerializationStrategy/SignalTypeConstants.h"
#include "../SerializableObjects/SerializationStrategies/SignalSerializationStrategy/ParticularSignals/BadRequestSerializationStrategy/BadRequestSerializationStrategy.h"
using namespace std;

void builderInit(SerializableObjectBuilder* builder)
	{
	builder->addSerializableObjectBuilder(SERIALIZABLE_INTEGER, (SerializableObjectBuilder*)(new TerminalSerializableObjectBuilder<Integer>()));
	builder->addSerializableObjectBuilder(SERIALIZABLE_REAL, (SerializableObjectBuilder*)(new TerminalSerializableObjectBuilder<Real>()));
	builder->addSerializableObjectBuilder(SERIALIZABLE_STRING,(SerializableObjectBuilder*)(new TerminalSerializableObjectBuilder<String>()));
	builder->addSerializableObjectBuilder(SERIALIZABLE_RAW_BYTE_BUFFER, (SerializableObjectBuilder*)(new TerminalSerializableObjectBuilder<RawByteBuffer>()));
	builder->addSerializableObjectBuilder(SERIALIZABLE_SIGNAL, (SerializableObjectBuilder*)(new SignalBuilder()));
	(*builder)[SERIALIZABLE_SIGNAL]->addSerializableObjectBuilder(SIGNAL_BAD_REQUEST, (SerializableObjectBuilder*)(new TerminalSerializableObjectBuilder<BadRequest>()));
	}

list<SerializableObject*>* riceviParametri(TcpIpActiveSocket* socket)
	{
	list<SerializableObject*>::size_type listSize = 0;
	list<SerializableObject*>::size_type* listSizePointer =
	(list<SerializableObject*>::size_type*)socket->receiveMessage(sizeof(list<SerializableObject*>::size_type));
	listSize = *listSizePointer;
	free(listSizePointer);
	//Ho la lunghezza della lista
	list<SerializableObject*>* parameterList = new list<SerializableObject*>();
	SerializableObjectBuilder builder;
	builderInit(&builder);
	for(int i = 0; i < listSize; i++)
		{
		Type* receivedTypePointer = ((Type*)socket->receiveMessage(sizeof(Type)));
		Type receivedType = *receivedTypePointer;
		free(receivedTypePointer);
		//OK??
		int valueLengthLength = builder.getValueLengthLength(receivedType);
		uint64_t valueLength =
			(valueLengthLength == 0)? 0:
		    (valueLengthLength == sizeof(uint8_t ))?
		    *((uint8_t*)socket->receiveMessage(sizeof(uint8_t))) :
		    (valueLengthLength == sizeof(uint16_t))?
		    *((uint16_t*)socket->receiveMessage(sizeof(uint16_t))) :
		    (valueLengthLength == sizeof(uint32_t))?
		    *((uint32_t*)socket->receiveMessage(sizeof(uint32_t))) :
		    (valueLengthLength == sizeof(uint64_t))?
		    *((uint64_t*)socket->receiveMessage(sizeof(uint64_t))) : 0;
		void* value = (valueLength == 0)? NULL : socket->receiveMessage(valueLength);
		parameterList->push_back(builder.delegateBuilding(receivedType, valueLength, value));
		}
	return parameterList;
	}

int main()
	{
	try{
	TcpIpPassiveSocket listeningSocket(4000, 5);
	cout << "Server: ascolto" << endl;
	TcpIpActiveSocket* socket = listeningSocket.acceptConnection();
	cout << "Server: ho ricevuto una richiesta" << endl;
	list<SerializableObject*>* inputList = riceviParametri(socket);
	list<SerializableObject*>::iterator i = inputList->begin();
	for(; i != inputList->end(); i++)
		{
		cout << "Input parameter type: " << (*i)->getType() << endl;
		}
    i = inputList->begin();
    while((*i)->getType() != SERIALIZABLE_RAW_BYTE_BUFFER) i++;
	SerializableObject* r = /*dynamic_cast<RawByteBuffer*>*/(*i);
	ByteArray* pb = (ByteArray*)(r->getValue());
	ofstream outfile ("ricevutoDalClientInOutput.jpg",ofstream::binary);
	outfile.write( (char*)( pb->getPointer() ) , pb->getLength() );
	delete pb;
	char * memblock;
	ifstream::pos_type size;
	ifstream file ("tux.jpg", ios::in|ios::binary|ios::ate);
	if (file.is_open())
		{
	    size = file.tellg();
	    memblock = new char [size];
	    file.seekg (0, ios::beg);
	    file.read (memblock, size);
	    file.close();
	    cout << "the complete file content is in memory";
	    }
	else cout << "Unable to open file";
	ByteArray fileBytes((void*)memblock, size);
	RawByteBuffer objectToSend(fileBytes);
	list<SerializableObject*>::size_type dimensioneee = (list<SerializableObject*>::size_type)2;
	socket->sendMessage(&dimensioneee, sizeof(list<SerializableObject*>::size_type));
	void* serializedObject = NULL;
	uint64_t serializedObjectLength = objectToSend.serialize(&serializedObject);
	cout << "Lunghezza del file di risposta: " << serializedObjectLength << endl;
	socket->sendMessage(serializedObject, serializedObjectLength);
	free(serializedObject);
	serializedObject = NULL;
	BadRequest b;
	serializedObjectLength = b.serialize(&serializedObject);
	cout << "TIPO RITORNATO: " << *((Type*)(serializedObject)) << endl;
    cout << "\t lunghezza del campo value: " << (int)(*((uint8_t*)(((Type*)(serializedObject))+1))) << endl;
    cout << "\t campo value: " << *((Type*)(((uint8_t*)(((Type*)(serializedObject))+1))+1)) << endl;
    cout << "Lunghezza del messaggio serializzato: " << serializedObjectLength << endl;
	socket->sendMessage(serializedObject, serializedObjectLength);
	free(serializedObject);
	serializedObject = NULL;
	}
	catch(exception& e)
	{
	cout << e.what() << endl;
	}
	catch(...)
	{
	cout << "Eccezione ignota" << endl;
	}
	return 0;
	}
