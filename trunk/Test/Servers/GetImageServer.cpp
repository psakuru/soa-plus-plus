#include "GetImageServer.h"
#include "../../SerializableObjects/SerializationStrategies/RawByteBufferSerializationStrategy/RawByteBufferSerializationStrategy.h"
#include "../../SerializableObjects/SerializationStrategies/StringSerializationStrategy/StringSerializationStrategy.h"
#include "../../SerializableObjects/SerializationStrategies/SignalSerializationStrategy/ParticularSignals/GenericSignalSerializationStrategy/GenericSignalSerializationStrategy.h"
#include "../../SerializableObjects/SerializationStrategies/SignalSerializationStrategy/ParticularSignals/ImageNotFoundSerializationStrategy/ImageNotFoundSerializationStrategy.h"
#include "../../SerializableObjects/DeserializationStrategies/TerminalSerializableObjectBuilder.h"
#include "../../ObjectInterfaces/SingletonObject/SingletonObject.h"
#include "../../ObjectInterfaces/SerializableObject/SerializableObject.h"
#include "../../SerializableObjects/Utilities/ByteArray/ByteArray.h"
#include "../../Utilities/ColorPrint/ColorPrint.h"
#include "Utilities/UtilityFunctions.h"
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
        cout << BLUE_TXT << "Request for file: " << GREEN_TXT << name.c_str() << DEFAULT << endl;
        // Inserisco l'immagine nei parametri di output.
        RawByteBuffer* objectToBeSent = loadImage(name);
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


