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
#include "../../Utilities/ColorPrint/ColorPrint.h"
#include "Utilities/UtilityFunctions.h"
#include "../CImg/CImg.h"
#include "HorizontalFlipImageServer.h"
#include <boost/lexical_cast.hpp>
#include <unistd.h>
using namespace std;
using namespace cimg_library;

void HorizontalFlipImage::doService()
{
    cout << BLUE_TXT << "Horizontal flip request received" << DEFAULT << endl;
	// Recupero i parametri di input.
	SerializableObjectList::iterator i = inputParameters.begin();
	SerializableObject* r = (*i);
	ByteArray* bufferPointer = (ByteArray*)(r->getValue());
	// Salvo l'immagine ricevuta.
	string name;
	stringstream threadIDToStringConverter;
	threadIDToStringConverter << boost::this_thread::get_id();
	threadIDToStringConverter >> name;
	name.append(boost::lexical_cast(getpid()));
	name.append(".jpg");
	storeImage(name,bufferPointer);
	delete bufferPointer;
	// Eseguo il flip.
	CImg<unsigned char> image;
	image = image.load_jpeg(name.c_str());
	image.mirror('x');
	image.save_jpeg(name.c_str(),90U);
	// Inserisco l'immagine modificata nei parametri di output in modo che sia inviata come risposta.
	RawByteBuffer* objectToBeSent = loadImage(name);
	outputParameters.push_back(objectToBeSent);
	cout << BLUE_TXT << "Image flipped" << DEFAULT << endl;
}
HorizontalFlipImage::HorizontalFlipImage() : Skeleton("HorizontalFlipImage"), RegistrablePoolableCyclicCallableSkeleton("HorizontalFlipImage")
{
	// Aggiungo al serviceId e alla lista di input i parametri che mi aspetto di ricevere.
	addParameter(new RawByteBuffer, IN);
	addParameter(new RawByteBuffer, INOUT);
}

