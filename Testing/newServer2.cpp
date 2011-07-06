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
using namespace std;

class ParticularRegistrablePoolableCyclicCallableSkeleton : public RegistrablePoolableCyclicCallableSkeleton
{
protected:
    void doService()
    {
        cout << "TID:" << boost::this_thread::get_id() << " chiamata ricevuta" << endl << endl;
        /* <ricezione e store> */
        SerializableObjectList::iterator i = inputParameters.begin();
        while((*i)->getType() != SERIALIZABLE_RAW_BYTE_BUFFER) i++;
        SerializableObject* r = (*i);
        ByteArray* pb = (ByteArray*)(r->getValue());
        ofstream outfile ("ricevutoDalClientIninput.jpg",ofstream::binary | ofstream::out);
        outfile.write( (char*)( pb->getPointer() ) , pb->getLength() );
        outfile.close();
        delete pb;
        /* </ricezione e store> */
        char * memblock;
        uint64_t size = 0;
        ifstream file ("tux.jpg", ios::in|ios::binary|ios::ate);
        if (file.is_open())
        {
            size = (int)file.tellg();
            memblock = (char*)malloc(size);
            file.seekg (0, ios::beg);
            file.read (memblock, size);
            file.close();

        }
        else cout << "Unable to open file";
        ByteArray* fileBytes = new ByteArray((void*)memblock, size);
        free(memblock);
        RawByteBuffer* objectToSend = new RawByteBuffer(fileBytes, false);
        BadRequest* badRequest = new BadRequest();
        outputParameters.push_back(objectToSend); //Tanto poi ci pensa la lista boost a fare la delete!
        outputParameters.push_back(badRequest);
    }
public:
    ParticularRegistrablePoolableCyclicCallableSkeleton()
        : Skeleton("redHat"), RegistrablePoolableCyclicCallableSkeleton("redHat") //Diamond problem fix!
    {
        cout << "TID:" << boost::this_thread::get_id() << " ParticularPoolableCyclicCallableSkeleton()" << endl << endl;
        addParameter(new Integer, IN);
        addParameter(new Real, IN);
        addParameter(new String, IN);
        addParameter(new RawByteBuffer, INOUT);
        addParameter(new BadRequest, INOUT);
        /*inputParameters.push_back(new Integer);
        inputParameters.push_back(new Real);
        inputParameters.push_back(new String);
        inputParameters.push_back(new RawByteBuffer);
        inputParameters.push_back(new BadRequest);*/
    }
};



int main()
{
    try{
    RegistrableObject* r = new RegistrableSkeletonThreadPool< RegistrablePoolableCallableSkeletonWrapper<ParticularRegistrablePoolableCyclicCallableSkeleton>, 3 >("127.0.0.1", 3002, SOMAXCONN);
    char a= 'a';
    cin >> a;
    Publisher p("127.0.0.1:4000");
    p.setPublishingMode(publish);
    p.addObjectToPublish(r);
    p();
    while(1){}
    }
     catch(exception& e)
    	{
    	cout << e.what() << endl;
    	}
    return 0;
}

