#include <iostream>
#include <fstream>
#include "../../ObjectInterfaces/SerializableObject/SerializableObject.h"
#include "../../SerializableObjects/Utilities/ByteArray/ByteArray.h"
#include "../../ServiceOrientedArchitecture/Service/Skeleton/RegistrablePoolableCyclicCallableSkeleton/RegistrablePoolableCyclicCallableSkeleton.h"
#include "../../ServiceOrientedArchitecture/Service/Skeleton/Utilities/PoolableCallableSkeletonWrappers/RegistrablePoolableCallableSkeletonWrapper/RegistrablePoolableCallableSkeletonWrapper.h"
#include "../../ServiceOrientedArchitecture/Service/Skeleton/SkeletonThreadPool/RegistrableSkeletonThreadPool/RegistrableSkeletonThreadPool.h"
#include "../../SerializableObjects/SerializationStrategies/RawByteBufferSerializationStrategy/RawByteBufferSerializationStrategy.h"
#include "../../SerializableObjects/SerializationStrategies/IntegerSerializationStrategy/IntegerSerializationStrategy.h"
#include "../../SerializableObjects/SerializationStrategies/StringSerializationStrategy/StringSerializationStrategy.h"
#include "../../ServiceOrientedArchitecture/Publisher/Publisher.h"
#include "../../ObjectInterfaces/RegistrableObject/RegistrableObject.h"
#include "boost/thread/thread.hpp"
#include "../CImg/CImg.h"
#include "stdint.h"
#include "RotateImageServer.h"
using namespace std;
using namespace cimg_library;

void RotateImage::doService()
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
RotateImage::RotateImage() : Skeleton("RotateImage"), RegistrablePoolableCyclicCallableSkeleton("RotateImage")
{
	// Aggiungo al serviceId e alla lista di input i parametri che mi aspetto di ricevere.
	addParameter(new Integer, IN);
	addParameter(new RawByteBuffer, IN);
	addParameter(new RawByteBuffer, INOUT);
}
