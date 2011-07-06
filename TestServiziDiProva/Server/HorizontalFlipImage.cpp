#define cimg_use_jpeg
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
using namespace std;
using namespace cimg_library;

class HorizontalFlipImage : public RegistrablePoolableCyclicCallableSkeleton
{
protected:
	void doService()()
    {
        cout << "TID:" << boost::this_thread::get_id() << " chiamata ricevuta" << endl << endl;
        /* ricezione e store */
        SerializableObjectList::iterator i = inputParameters.begin();
        SerializableObject* r = (*i);
        ByteArray* pb = (ByteArray*)(r->getValue());

        //TODO ECCEZIONI!!
        ofstream outfile ("imageReceived.jpg",ofstream::binary | ofstream::out);
        outfile.write( (char*)( pb->getPointer() ) , pb->getLength() );
        outfile.close();
        delete pb;
        /* /ricezione e store */
        /* manipolazione */
        CImg<unsigned char> image;
        image = image.load_jpeg("imageReceived.jpg");
        image.mirror('x');
        image.save_jpeg("imageToBeSent.jpg",90U);
        remove("imageReceived.jpg");
        /* invio */
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
      //  BadRequest* badRequest = new BadRequest();
        outputParameters.push_back(objectToBeSent); //Tanto poi ci pensa la lista boost a fare la delete!
      //  outputParameters.push_back(badRequest);
    }
public:
	HorizontalFlipImage()
        : Skeleton("RotateImage"), RegistrablePoolableCyclicCallableSkeleton("RotateImage") //Diamond problem fix!
    {
        //cout << "TID:" << boost::this_thread::get_id() << " ParticularPoolableCyclicCallableSkeleton()" << endl << endl;
    	addParameter(new RawByteBuffer, IN);
    	addParameter(new RawByteBuffer, INOUT);
        addParameter(new BadRequest, INOUT);
        /*inputParameters.push_back(new Integer);
        inputParameters.push_back(new Real);
        inputParameters.push_back(new String);
        inputParameters.push_back(new RawByteBuffer);
        inputParameters.push_back(new BadRequest);*/
    }
};
