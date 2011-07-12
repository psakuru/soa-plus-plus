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
#include "../../ObjectInterfaces/SingletonObject/SingletonObject.h"
#include <boost/lexical_cast.hpp>
#include <unistd.h>
using namespace std;
using namespace cimg_library;

void RotateImageServer::doService()
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
	string name = uniqueID;
	storeImage(name,pb);
	delete pb;
	// Ruoto.
	CImg<float> image;
	image = image.load_jpeg(name.c_str());
	direction = direction % 360;
	image = image.rotate((float)direction);
	image.save_jpeg(name.c_str());
	remove(name.c_ster());
	// Inserisco l'immagine ruotata nei parametri di output in modo che sia inviata come risposta.
	RawByteBuffer* objectToBeSent = loadImage(name);
	outputParameters.push_back(objectToBeSent);
	cout << GREEN_TXT << "Immagine ruotata" << DEFAULT << endl;
}
RotateImageServer::RotateImageServer() : Skeleton("RotateImage"), RegistrablePoolableCyclicCallableSkeleton("RotateImage")
{
	univocalNumberGenerator = SingletonObject<UnivocalNumberGenerator>::getInstance();
	uniqueID = "r";
	uniqueID.append(boost::lexical_cast<string>(univocalNumberGenerator->getUnivocalNumber()));
	uniqueID.append(".jpg");
	// Aggiungo al serviceId e alla lista di input i parametri che mi aspetto di ricevere.
	addParameter(new Integer, IN);
	addParameter(new RawByteBuffer, IN);
	addParameter(new RawByteBuffer, INOUT);
}
