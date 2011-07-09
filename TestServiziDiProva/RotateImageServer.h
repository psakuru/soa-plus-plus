/**
 * @file RotateImageServer.h
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
#include "../ObjectInterfaces/SerializableObject/SerializableObject.h"
#include "../SerializableObjects/Utilities/ByteArray/ByteArray.h"
#include "../ServiceOrientedArchitecture/Service/Skeleton/RegistrablePoolableCyclicCallableSkeleton/RegistrablePoolableCyclicCallableSkeleton.h"
#include "../ServiceOrientedArchitecture/Service/Skeleton/Utilities/PoolableCallableSkeletonWrappers/RegistrablePoolableCallableSkeletonWrapper/RegistrablePoolableCallableSkeletonWrapper.h"
#include "../ServiceOrientedArchitecture/Service/Skeleton/SkeletonThreadPool/RegistrableSkeletonThreadPool/RegistrableSkeletonThreadPool.h"
#include "../ServiceOrientedArchitecture/Publisher/Publisher.h"
#include "../ObjectInterfaces/RegistrableObject/RegistrableObject.h"
#include "boost/thread/thread.hpp"
#include "CImg/CImg.h"
#include "stdint.h"
using namespace std;
using namespace cimg_library;

class RotateImage : public RegistrablePoolableCyclicCallableSkeleton
{
protected:
	void doService()
    {
		// Recupero i parametri di input.
        SerializableObjectList::iterator i = inputParameters.begin();
        int32_t* directionPointer = (int32_t*)((*i)->getValue());
		int32_t direction = *directionPointer;
		delete directionPointer;
        i++;
        ByteArray* pb = (ByteArray*)((*i)->getValue());
        // Salvo l'immagine ricevuta.
		string name;
		stringstream threadIDToStringConverter;
		threadIDToStringConverter << boost::this_thread::get_id();
		threadIDToStringConverter >> name;
		name.append(".jpg");
        ofstream outfile (name.c_str(),ofstream::binary | ofstream::out);
        outfile.write( (char*)( pb->getPointer() ) , pb->getLength() );
        outfile.close();
        delete pb;
		// Ruoto.
        CImg<unsigned char> image;
        image = image.load_jpeg(name.c_str());
		direction = direction % 360;
        image.rotate((float)direction,0,1);
        image.save_jpeg(name.c_str(),90U);
		// Inserisco l'immagine ruotata nei parametri di output in modo che sia inviata come risposta.
        char * memblock;
        uint64_t size = 0;
        ifstream file (name.c_str(), ios::in|ios::binary|ios::ate);
        size = (int)file.tellg();
		memblock = (char*)malloc(size);
		file.seekg (0, ios::beg);
		file.read (memblock, size);
		file.close();
        ByteArray* fileBytes = new ByteArray((void*)memblock, size);
        free(memblock);
        remove(name.c_str());
        RawByteBuffer* objectToBeSent = new RawByteBuffer(fileBytes, false);
		outputParameters.push_back(objectToBeSent);
	}
public:
    RotateImage()
        : Skeleton("RotateImage"), RegistrablePoolableCyclicCallableSkeleton("RotateImage")
    {
		// Aggiungo al serviceId e alla lista di input i parametri che mi aspetto di ricevere.
    	addParameter(new Integer, IN);
    	addParameter(new RawByteBuffer, IN);
    	addParameter(new RawByteBuffer, INOUT);
	}
};
