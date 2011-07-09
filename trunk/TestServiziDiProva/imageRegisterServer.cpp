#include <iostream>
#include <fstream>
#include <list>
#include <exception>
#include <boost/thread/barrier.hpp>
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
#include "StoreImageServer.h"
#include "GetImageServer.h"
#include "GetListServer.h"
using namespace std;



int main()
{
    try{
    RegistrableObject* r = new RegistrableSkeletonThreadPool< RegistrablePoolableCallableSkeletonWrapper<StoreImage> >(3, "127.0.0.1", 5000, SOMAXCONN);
    RegistrableObject* s = new RegistrableSkeletonThreadPool< RegistrablePoolableCallableSkeletonWrapper<GetImage> >(3, "127.0.0.1", 5001, SOMAXCONN);
    RegistrableObject* t = new RegistrableSkeletonThreadPool< RegistrablePoolableCallableSkeletonWrapper<GetList> >(3, "127.0.0.1", 5002, SOMAXCONN);
    char a= 'a';
    cin >> a;
    Publisher p("127.0.0.1:4000");
    p.setPublishingMode(publish);
    p.addObjectToPublish(r);
    p.addObjectToPublish(s);
    p.addObjectToPublish(t);
    p();
    boost::barrier blockingBarrier(2);
    blockingBarrier.wait();
    //while(1){}
    }
     catch(exception& e)
    	{
    	cout << e.what() << endl;
    	}
    return 0;
}

