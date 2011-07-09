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
#include "../ServiceOrientedArchitecture/Service/Skeleton/RegistrablePoolableCyclicCallableSkeleton/RegistrablePoolableCyclicCallableSkeleton.h"
#include "../SerializableObjects/SerializationStrategies/StringSerializationStrategy/StringSerializationStrategy.h"
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
		//TODO Se l'immagine non è presente??
		if(!sharedState->findString(name))
		{
		    return;
			//TODO ECCEZIONE - il file non esiste o comunque non è stato registrato.
		}
		char* memblock;
		uint64_t size = 0;
		ifstream file(name.c_str(), ios::in | ios::binary | ios::ate);
		if (file.is_open())
		{
			size = (int) file.tellg();
			memblock = (char*) malloc(size);
			file.seekg(0, ios::beg);
			file.read(memblock, size);
			file.close();

		}
		else
		{
			//TODO ECCEZIONE - fare un try chatch con un robo che comunque faccia a remove del file
		}
		// Inserisco l'immagine nei parametri di output.
		ByteArray* fileBytes = new ByteArray((void*)memblock, size);
		free(memblock);
		remove(name.c_str());
		RawByteBuffer* objectToBeSent = new RawByteBuffer(fileBytes, false);
		outputParameters.push_back(objectToBeSent);
    }
public:
    GetImage() : Skeleton("GetImage"), RegistrablePoolableCyclicCallableSkeleton("GetImage")
    {
        sharedState = SingletonObject<ImageRegisterSharedState>::getInstance();
        addParameter(new String, IN);
        addParameter(new RawByteBuffer, INOUT);
    }
};
