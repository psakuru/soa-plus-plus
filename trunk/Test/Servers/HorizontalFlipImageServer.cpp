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
#include "../../ObjectInterfaces/SingletonObject/SingletonObject.h"
#include "../../Utilities/ColorPrint/ColorPrint.h"
#include "Utilities/UtilityFunctions.h"
#include "../CImg/CImg.h"
#include "HorizontalFlipImageServer.h"
#include <boost/lexical_cast.hpp>
#include <unistd.h>
using namespace std;
using namespace cimg_library;

void HorizontalFlipImageServer::doService()
{
    cout << BLUE_TXT << "Horizontal flip request received" << DEFAULT << endl;
	// Recupero i parametri di input.
	SerializableObjectList::iterator i = inputParameters.begin();
	SerializableObject* r = (*i);
	ByteArray* bufferPointer = (ByteArray*)(r->getValue());
	// Salvo l'immagine ricevuta.
	string name = uniqueID;
	storeImage(name,bufferPointer);
	delete bufferPointer;
	// Eseguo il flip.
	CImg<float> image;
	image = image.load_jpeg(name.c_str());
	image = image.mirror('x');
	image.save_jpeg(name.c_str());
	// Inserisco l'immagine modificata nei parametri di output in modo che sia inviata come risposta.
	RawByteBuffer* objectToBeSent = loadImage(name);
	outputParameters.push_back(objectToBeSent);
	cout << BLUE_TXT << "Image flipped" << DEFAULT << endl;
}
HorizontalFlipImageServer::HorizontalFlipImageServer() : Skeleton("HorizontalFlipImage"), RegistrablePoolableCyclicCallableSkeleton("HorizontalFlipImage")
{
	univocalNumberGenerator = SingletonObject<UnivocalNumberGenerator>::getInstance();
	uniqueID = "h";
	uniqueID.append(boost::lexical_cast<string>(univocalNumberGenerator->getUnivocalNumber()));
	uniqueID.append(".jpg");
	// Aggiungo al serviceId e alla lista di input i parametri che mi aspetto di ricevere.
	addParameter(new RawByteBuffer, IN);
	addParameter(new RawByteBuffer, INOUT);
}

