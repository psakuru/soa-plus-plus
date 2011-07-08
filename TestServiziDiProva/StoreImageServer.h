/**
 * @file StoreImage.h
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

class StoreImage : public RegistrablePoolableCyclicCallableSkeleton
{
private:
    ImageRegisterSharedState* sharedState;
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
        boost::unique_lock<boost::shared_mutex> writersLock(sharedState->sharedMutex);
        SerializableObjectList::iterator i = inputParameters.begin();
        string* entry = (string*)((*i)->getValue());
        string name = *entry;
        delete entry;
        i++;
        ByteArray* receivedImage = (ByteArray*)((*i)->getValue());
        ofstream outfile(name.c_str(), ofstream::binary | ofstream::out);
        outfile.write((char*) (receivedImage->getPointer()), receivedImage->getLength());
        outfile.close();
        delete receivedImage;
        if(!findString(name))
        {
            sharedState->imageList.push_front(name);
        }
    }
public:
    StoreImage() : Skeleton("StoreImage"), RegistrablePoolableCyclicCallableSkeleton("StoreImage")
    {
        sharedState = SingletonObject<ImageRegisterSharedState>::getInstance();
        addParameter(new String, IN);
        addParameter(new RawByteBuffer, IN);
    }
};