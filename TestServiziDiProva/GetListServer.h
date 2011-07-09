/**
 * @file GetListServer.h
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

class GetList : public RegistrablePoolableCyclicCallableSkeleton
{
private:
	// Stato condiviso fra i thread del pool.
    ImageRegisterSharedState* sharedState;
	// Funzione di utilità per la ricerca di una stringa in una lista di stringhe.
    bool findString(string stringToBeSearched)
    {
        list<string>::iterator i = sharedState->imageList.begin();
        for(; i != sharedState->imageList.end(); i++)
        {
            if(((*i).compare(stringToBeSearched)) == 0)
            {
                return true;
            }
        }
        return false;
    }
protected:
    void doService()
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
public:
    GetList() : Skeleton("GetList"), RegistrablePoolableCyclicCallableSkeleton("GetList")
    {
		// Stato condiviso fra i thread del pool. E' un'istanza singleton.
        sharedState = SingletonObject<ImageRegisterSharedState>::getInstance();
		// Aggiungo i parametri che mi aspetto di ricevere al serviceID e alla lista di input.
        addParameter(new String, INOUT);
    }
};
