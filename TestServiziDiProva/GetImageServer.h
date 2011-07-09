/**
 * @file GetImageServer.h
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
#include "../ObjectInterfaces/SerializableObject/SerializableObject.h"
#include "../SerializableObjects/Utilities/ByteArray/ByteArray.h"
#include "../ServiceOrientedArchitecture/Service/Skeleton/RegistrablePoolableCyclicCallableSkeleton/RegistrablePoolableCyclicCallableSkeleton.h"
#include "../ServiceOrientedArchitecture/Service/Skeleton/Utilities/PoolableCallableSkeletonWrappers/RegistrablePoolableCallableSkeletonWrapper/RegistrablePoolableCallableSkeletonWrapper.h"
#include "../ServiceOrientedArchitecture/Service/Skeleton/SkeletonThreadPool/RegistrableSkeletonThreadPool/RegistrableSkeletonThreadPool.h"
#include "../SerializableObjects/SerializationStrategies/RawByteBufferSerializationStrategy/RawByteBufferSerializationStrategy.h"
#include "../SerializableObjects/SerializationStrategies/IntegerSerializationStrategy/IntegerSerializationStrategy.h"
#include "../ServiceOrientedArchitecture/Publisher/Publisher.h"
#include "../ObjectInterfaces/RegistrableObject/RegistrableObject.h"
#include "../SerializableObjects/SerializationStrategies/SignalSerializationStrategy/ParticularSignals/GenericSignalSerializationStrategy/GenericSignalSerializationStrategy.h"
#include "../SerializableObjects/SerializationStrategies/SignalSerializationStrategy/ParticularSignals/ImageNotFoundSerializationStrategy/ImageNotFoundSerializationStrategy.h"
#include "ImageRegisterSharedState.h"
#include <string>
#include <list>
#include <iostream>
#include <stdio.h>
using namespace std;

class GetImage : public RegistrablePoolableCyclicCallableSkeleton
{
private:
    ImageRegisterSharedState* sharedState;
protected:
    void doService()
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
		char* memblock;
		uint64_t size = 0;
		ifstream file(name.c_str(), ios::in | ios::binary | ios::ate);
	
			size = (int) file.tellg();
			memblock = (char*) malloc(size);
			file.seekg(0, ios::beg);
			file.read(memblock, size);
			file.close();
		// Inserisco l'immagine nei parametri di output.
		ByteArray* fileBytes = new ByteArray((void*)memblock, size);
		free(memblock);
		remove(name.c_str());
		RawByteBuffer* objectToBeSent = new RawByteBuffer(fileBytes, false);
		outputParameters.push_back(objectToBeSent);
		GenericSignalWrapper* signal = new GenericSignalWrapper();
		outputParameters.push_back(signal);
		}
		else 
		{
			// Alla deserializzazione del segnale verrà richiamato il suo handler che gestirà
			// la situazione di errore (immagine non presente sul server).
			ByteArray* fileBytes = new ByteArray((void*)memblock, size);
			free(memblock);
			remove(name.c_str());
			RawByteBuffer* objectToBeSent = new RawByteBuffer(fileBytes, false);
			outputParameters.push_back(objectToBeSent);
			ImageNotFound* signal = new ImageNotFound();
			outputParameters.push_back(signal);
		}

    }
public:
    GetImage() : Skeleton("GetImage"), RegistrablePoolableCyclicCallableSkeleton("GetImage")
    {
        sharedState = SingletonObject<ImageRegisterSharedState>::getInstance();
        addParameter(new String, IN);
        addParameter(new RawByteBuffer, INOUT);
		addParameter(new GenericSignalWrapper, INOUT);
    }
};
