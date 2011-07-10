#define cimg_use_jpeg
#include <iostream>
#include <fstream>
#include <list>
#include <exception>
#include "../../ObjectInterfaces/SerializableObject/SerializableObject.h"
#include "../../SerializableObjects/Utilities/ByteArray/ByteArray.h"
#include "../../ServiceOrientedArchitecture/Service/Skeleton/RegistrablePoolableCyclicCallableSkeleton/RegistrablePoolableCyclicCallableSkeleton.h"
#include "../../ServiceOrientedArchitecture/Service/Skeleton/Utilities/PoolableCallableSkeletonWrappers/RegistrablePoolableCallableSkeletonWrapper/RegistrablePoolableCallableSkeletonWrapper.h"
#include "../../ServiceOrientedArchitecture/Service/Skeleton/SkeletonThreadPool/RegistrableSkeletonThreadPool/RegistrableSkeletonThreadPool.h"
#include "../../SerializableObjects/SerializationStrategies/RawByteBufferSerializationStrategy/RawByteBufferSerializationStrategy.h"
#include "../../ServiceOrientedArchitecture/Publisher/Publisher.h"
#include "../../ObjectInterfaces/RegistrableObject/RegistrableObject.h"
#include "../CImg/CImg.h"
#include "HorizontalFlipImageServer.h"
using namespace std;
using namespace cimg_library;

void HorizontalFlipImage::doService()
{
	// Recupero i parametri di input.
	SerializableObjectList::iterator i = inputParameters.begin();
	SerializableObject* r = (*i);
	ByteArray* pb = (ByteArray*)(r->getValue());
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
	// Eseguo il flip.
	CImg<unsigned char> image;
	image = image.load_jpeg(name.c_str());
	image.mirror('x');
	image.save_jpeg(name.c_str(),90U);
	// Inserisco l'immagine modificata nei parametri di output in modo che sia inviata come risposta.
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
HorizontalFlipImage::HorizontalFlipImage() : Skeleton("HorizontalFlipImage"), RegistrablePoolableCyclicCallableSkeleton("HorizontalFlipImage")
{
	// Aggiungo al serviceId e alla lista di input i parametri che mi aspetto di ricevere.
	addParameter(new RawByteBuffer, IN);
	addParameter(new RawByteBuffer, INOUT);
}

