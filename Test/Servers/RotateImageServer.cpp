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
#include "../../Utilities/ColorPrint/ColorPrint.h"
#include "Utilities/UtilityFunctions.h"
#include "boost/thread/thread.hpp"
#include "../CImg/CImg.h"
#include "stdint.h"
#include "RotateImageServer.h"
using namespace std;
using namespace cimg_library;

void RotateImage::doService()
{
    cout << GREEN_TXT << "Richiesta di rotazione ricevuta" << DEFAULT << endl;
	// Recupero i parametri di input.
	SerializableObjectList::iterator i = inputParameters.begin();
	int32_t* directionPointer = (int32_t*)((*i)->getValue());
	int32_t direction = *directionPointer;
	cout << RED_TXT << "Rotazione: " << direction << " gradi" << DEFAULT << endl;
	delete directionPointer;
	i++;
	ByteArray* pb = (ByteArray*)((*i)->getValue());
	// Salvo l'immagine ricevuta.
	string name;
	stringstream threadIDToStringConverter;
	threadIDToStringConverter << boost::this_thread::get_id();
	threadIDToStringConverter >> name;
	name.append(".jpg");
	storeImage(name,pb);
	delete pb;
	// Ruoto.
	CImg<unsigned char> image;
	image = image.load_jpeg(name.c_str());
	direction = direction % 360;
	image.rotate((float)direction,0,1);
	image.save_jpeg(name.c_str(),90U);
	// Inserisco l'immagine ruotata nei parametri di output in modo che sia inviata come risposta.
	RawByteBuffer* objectToBeSent = loadImage(name);
	outputParameters.push_back(objectToBeSent);
	// Rimuovo l'immagine temporaneamente salvata.
	remove(name.c_str());
	cout << GREEN_TXT << "Immagine ruotata" << DEFAULT << endl;
}
RotateImage::RotateImage() : Skeleton("RotateImage"), RegistrablePoolableCyclicCallableSkeleton("RotateImage")
{
	// Aggiungo al serviceId e alla lista di input i parametri che mi aspetto di ricevere.
	addParameter(new Integer, IN);
	addParameter(new RawByteBuffer, IN);
	addParameter(new RawByteBuffer, INOUT);
}
