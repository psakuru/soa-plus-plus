#include "GetImageServer.h"
#include "../../SerializableObjects/SerializationStrategies/RawByteBufferSerializationStrategy/RawByteBufferSerializationStrategy.h"
#include "../../SerializableObjects/SerializationStrategies/StringSerializationStrategy/StringSerializationStrategy.h"
#include "../../SerializableObjects/SerializationStrategies/SignalSerializationStrategy/ParticularSignals/GenericSignalSerializationStrategy/GenericSignalSerializationStrategy.h"
#include "../../SerializableObjects/SerializationStrategies/SignalSerializationStrategy/ParticularSignals/ImageNotFoundSerializationStrategy/ImageNotFoundSerializationStrategy.h"
#include "../../SerializableObjects/DeserializationStrategies/TerminalSerializableObjectBuilder.h"
#include "../../ObjectInterfaces/SingletonObject/SingletonObject.h"
#include "../../ObjectInterfaces/SerializableObject/SerializableObject.h"
#include "../../SerializableObjects/Utilities/ByteArray/ByteArray.h"
#include <boost/thread/shared_mutex.hpp>
#include <boost/thread/locks.hpp>
#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include <stdio.h>
using namespace std;

void GetImage::doService()
{
    // Acquisisco il lock sulla lista.
    boost::shared_lock<boost::shared_mutex> readersLock(sharedState->sharedMutex);
    // Recupero i parametri di input.
    SerializableObjectList::iterator i = inputParameters.begin();
    string* entry = (string*)(*i)->getValue();
    string name = *entry;
    delete entry;
    if(sharedState->findString(name))
    {
        cout << "Request fo file: " << name.c_str() << endl;
        char* memoryBlock;
        uint64_t size = 0;
        ifstream file(name.c_str(), ios::in | ios::binary | ios::ate);
        size = (int)file.tellg();
        memoryBlock = (char*)malloc(size);
        file.seekg(0, ios::beg); file.read(memoryBlock, size); file.close();
        // Inserisco l'immagine nei parametri di output.
        ByteArray* fileBytes = new ByteArray((void*)memoryBlock, size);
        free(memoryBlock);
        RawByteBuffer* objectToBeSent = new RawByteBuffer(fileBytes, false);
        outputParameters.push_back(objectToBeSent);
        GenericSignalWrapper* signal = new GenericSignalWrapper();
        outputParameters.push_back(signal);
    }
    else
    {
        // Alla deserializzazione del segnale verrà richiamato il suo handler che gestirà
        // la situazione di errore (immagine non presente sul server).
        RawByteBuffer* objectToBeSent = new RawByteBuffer();
        outputParameters.push_back(objectToBeSent);
        ImageNotFound* signal = new ImageNotFound();
        outputParameters.push_back(signal);
    }

}

GetImage::GetImage() : Skeleton("GetImage"), RegistrablePoolableCyclicCallableSkeleton("GetImage")
{
    sharedState = SingletonObject<ImageRegisterSharedState>::getInstance();
	addParameter(new String, IN);
    addParameter(new RawByteBuffer, INOUT);
    addParameter(new GenericSignalWrapper, INOUT);
}


