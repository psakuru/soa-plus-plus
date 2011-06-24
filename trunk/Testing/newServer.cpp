#include <iostream>
#include <fstream>
#include <list>
#include <exception>
#include "../TcpIpSocket/TcpIpPassiveSocket.h"
#include "../SerializableObjects/SerializableObject.h"
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
#include "../ServiceOrientedArchitecture/Service/Skeleton/PoolableCallableSkeleton/RegistrablePoolableCallableSkeletonWrapper/RegistrablePoolableCallableSkeletonWrapper.h"
#include "../ServiceOrientedArchitecture/Service/Skeleton/SkeletonThreadPool/RegistrableSkeletonThreadPool/RegistrableSkeletonThreadPool.h"
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
            //cout << "the complete file content is in memory, filesize: " << size << endl;
        }
        else cout << "Unable to open file";
        ByteArray* fileBytes = new ByteArray((void*)memblock, size); //TODO Questo è un Memory Leak!
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
    RegistrableSkeletonThreadPool< RegistrablePoolableCallableSkeletonWrapper<ParticularRegistrablePoolableCyclicCallableSkeleton>, 3 > pool("127.0.0.1", 4000, SOMAXCONN);
    while(1){}
    }
     catch(exception& e)
    	{
    	cout << e.what() << endl;
    	}
    return 0;
}

