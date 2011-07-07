/**
 * @file RotateImage.h
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

#include <iostream>
#include <fstream>
#include <list>
#include <exception>
#include "../TcpIpSocket/TcpIpPassiveSocket/TcpIpPassiveSocket.h"
#include "../ObjectInterfaces/SerializableObject/SerializableObject.h"
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
#include "../ServiceOrientedArchitecture/Service/Skeleton/RegistrablePoolableCyclicCallableSkeleton/RegistrablePoolableCyclicCallableSkeleton.h"
#include "../ServiceOrientedArchitecture/Service/Skeleton/Utilities/PoolableCallableSkeletonWrappers/RegistrablePoolableCallableSkeletonWrapper/RegistrablePoolableCallableSkeletonWrapper.h"
#include "../ServiceOrientedArchitecture/Service/Skeleton/SkeletonThreadPool/RegistrableSkeletonThreadPool/RegistrableSkeletonThreadPool.h"
#include "../ServiceOrientedArchitecture/Publisher/Publisher.h"
#include "../ObjectInterfaces/RegistrableObject/RegistrableObject.h"
#include "../CImg/CImg.h"
#include "stdint.h"
using namespace std;
using namespace cimg_library;

class RotateImage : public RegistrablePoolableCyclicCallableSkeleton
{
protected:
	void doService()()
    {
        
        SerializableObjectList::iterator i = inputParameters.begin();
        int32_t* directionPointer = (int32_t*)(d->getValue());
		int32_t direction = *directionPointer;
		delete directionPointer;
        i++;
        ByteArray* pb = (ByteArray*)(r->getValue());
        // Store.
        ofstream outfile ("imageReceived.jpg",ofstream::binary | ofstream::out);
        outfile.write( (char*)( pb->getPointer() ) , pb->getLength() );
        outfile.close();
        delete pb;
		// Manipulation.
        CImg<unsigned char> image;
        image = image.load_jpeg("imageReceived.jpg");
        image.rotate((float)direction,0,1);
        image.save_jpeg("imageToBeSent.jpg",90U);
        remove("imageReceived.jpg");
       
		/* metto nella lista di invio */
        char * memblock;
        uint64_t size = 0;
        ifstream file ("imageToBeSent.jpg", ios::in|ios::binary|ios::ate);
        if (file.is_open())
        {
            size = (int)file.tellg();
            memblock = (char*)malloc(size);
            file.seekg (0, ios::beg);
            file.read (memblock, size);
            file.close();

        }
        else {
        	//TODO ECCEZIONE - fare un try chatch con un robo che comunque faccia a remove del file
        }
        ByteArray* fileBytes = new ByteArray((void*)memblock, size);
        free(memblock);
        remove("imageToBeSent.jpg");
        RawByteBuffer* objectToBeSent = new RawByteBuffer(fileBytes, false);
		outputParameters.push_back(objectToBeSent);
	}
public:
    RotateImage()
        : Skeleton("RotateImage"), RegistrablePoolableCyclicCallableSkeleton("RotateImage")
    {
    	addParameter(new Integer, IN);
    	addParameter(new RawByteBuffer, IN);
    	addParameter(new RawByteBuffer, INOUT);
	}
};
