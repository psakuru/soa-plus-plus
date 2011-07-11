#include "../../ObjectInterfaces/SingletonObject/SingletonObject.h"
#include "../../ObjectInterfaces/SerializableObject/SerializableObject.h"
#include "../../SerializableObjects/Utilities/ByteArray/ByteArray.h"
#include "../../ServiceOrientedArchitecture/Service/Skeleton/RegistrablePoolableCyclicCallableSkeleton/RegistrablePoolableCyclicCallableSkeleton.h"
#include "../../ServiceOrientedArchitecture/Service/Skeleton/Utilities/PoolableCallableSkeletonWrappers/RegistrablePoolableCallableSkeletonWrapper/RegistrablePoolableCallableSkeletonWrapper.h"
#include "../../ServiceOrientedArchitecture/Service/Skeleton/SkeletonThreadPool/RegistrableSkeletonThreadPool/RegistrableSkeletonThreadPool.h"
#include "../../SerializableObjects/SerializationStrategies/RawByteBufferSerializationStrategy/RawByteBufferSerializationStrategy.h"
#include "../../SerializableObjects/SerializationStrategies/IntegerSerializationStrategy/IntegerSerializationStrategy.h"
#include "../../SerializableObjects/SerializationStrategies/StringSerializationStrategy/StringSerializationStrategy.h"
#include "../../ServiceOrientedArchitecture/Publisher/Publisher.h"
#include "../../Utilities/RegularExpressionChecker/RegularExpressionChecker.h"
#include "../../ObjectInterfaces/RegistrableObject/RegistrableObject.h"
#include "ImageRegisterSharedState.h"
#include "StoreImageServer.h"
#include <fstream>
#include <string>
#include <list>
#include <iostream>
#include <stdio.h>
using namespace std;

void StoreImage::doService()
{
	// Acquisisco il lock sulla lista.
	boost::unique_lock<boost::shared_mutex> writersLock(sharedState->sharedMutex);
	// Recupero i parametri di input.
	SerializableObjectList::iterator i = inputParameters.begin();
	string* entry = (string*)((*i)->getValue());
	string name = *entry;
	delete entry;
	RegularExpressionChecker checker = RegularExpressionChecker("\w*\.jpg");
	if(checker.checkForMatch(name))
	{
		i++;
		ByteArray* receivedImage = (ByteArray*)((*i)->getValue());
		ofstream outfile (name.c_str(),ofstream::binary | ofstream::out);
		outfile.write((char*) (receivedImage->getPointer()), receivedImage->getLength());
		outfile.close();
		delete receivedImage;
		// Inserisco il nome dell'immagine nella lista solamente se non è già presente.
		if(!sharedState->findString(name))
		{
			sharedState->imageList.push_front(name);
		}
	}
}
StoreImage::StoreImage() : Skeleton("StoreImage"), RegistrablePoolableCyclicCallableSkeleton("StoreImage")
{
	sharedState = SingletonObject<ImageRegisterSharedState>::getInstance();
	addParameter(new String, IN);
	addParameter(new RawByteBuffer, IN);
}

