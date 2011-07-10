#include "../../ObjectInterfaces/SingletonObject/SingletonObject.h"
#include "../../ObjectInterfaces/SerializableObject/SerializableObject.h"
#include "../../SerializableObjects/Utilities/ByteArray/ByteArray.h"
#include "../../ServiceOrientedArchitecture/Service/Skeleton/Utilities/PoolableCallableSkeletonWrappers/RegistrablePoolableCallableSkeletonWrapper/RegistrablePoolableCallableSkeletonWrapper.h"
#include "../../ServiceOrientedArchitecture/Service/Skeleton/SkeletonThreadPool/RegistrableSkeletonThreadPool/RegistrableSkeletonThreadPool.h"
#include "../../SerializableObjects/SerializationStrategies/RawByteBufferSerializationStrategy/RawByteBufferSerializationStrategy.h"
#include "../../SerializableObjects/SerializationStrategies/IntegerSerializationStrategy/IntegerSerializationStrategy.h"
#include "../../SerializableObjects/SerializationStrategies/StringSerializationStrategy/StringSerializationStrategy.h"
#include "../../ServiceOrientedArchitecture/Publisher/Publisher.h"
#include "../../ObjectInterfaces/RegistrableObject/RegistrableObject.h"
#include "GetListServer.h"
#include <string>
#include <list>
#include <iostream>
#include <stdio.h>
using namespace std;

GetList::doService()
{
	// Acquisisco il lock sulla lista.
	boost::shared_lock<boost::shared_mutex> readersLock(sharedState->sharedMutex);
	// Inserisco la lista nei parametri di output.
	string stringToReturn;
	list<string>::iterator i = sharedState->imageList.begin();
	for(; i != sharedState->imageList.end(); i++)
	{
		stringToReturn.append(*i).append(";");
	}
	outputParameters.push_back(new String(new string(stringToReturn), false));
}

GetList::GetList() : Skeleton("GetList"), RegistrablePoolableCyclicCallableSkeleton("GetList")
{
	// Stato condiviso fra i thread del pool. E' un'istanza singleton.
	sharedState = SingletonObject<ImageRegisterSharedState>::getInstance();
	// Aggiungo i parametri che mi aspetto di ricevere al serviceID e alla lista di input.
	addParameter(new String, INOUT);
}

