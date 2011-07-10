#include "../../ServiceOrientedArchitecture/Register/RegisterManager.h"
#include "../../ServiceOrientedArchitecture/Service/Skeleton/SkeletonThreadPool/RegistrableSkeletonThreadPool/RegistrableSkeletonThreadPool.h"
#include "../../ServiceOrientedArchitecture/Service/Skeleton/Utilities/PoolableCallableSkeletonWrappers/RegistrablePoolableCallableSkeletonWrapper/RegistrablePoolableCallableSkeletonWrapper.h"
#include "../../ServiceOrientedArchitecture/Register/Utilities/ExtensibleMap/MonitoredExtensibleMap/RRFIFOMonitoredExtensibleMap/RRFIFOMonitoredExtensibleMap.h"
#include "../../ServiceOrientedArchitecture/Publisher/Publisher.h"
#include <boost/lexical_cast.hpp>

int main(int argc, char** argv)
{
    if(argc < 4)
	{
		cout << "Usage: register <thread_pool_size> <listening_IP> <listening_port>";
		return 1;
	}
	try
	{
	    /* Pool di thread */
		RegistrableObject* serviceThreadPool =
		new RegistrableSkeletonThreadPool< RegistrablePoolableCallableSkeletonWrapper< RegisterManager< RRFIFOMonitoredExtensibleMap > > >
		(boost::lexical_cast<int>(argv[1]), argv[2], boost::lexical_cast<int>(argv[3]), SOMAXCONN);
		/* Graceful shutdown sequence */
		string shutdown;
		while(shutdown.compare("shutdown") != 0) cin >> shutdown; // Attesa del comando
		delete serviceThreadPool; //Graceful shutdown
    }
	catch(const exception& caughtException)
	{
    	cout << caughtException.what() << endl;
    	return 1;
	}
    return 0;



//    RegistrableObject* r =
//        new RegistrableSkeletonThreadPool
//    <
//    RegistrablePoolableCallableSkeletonWrapper
//    	<
//    	RegisterManager
//    		<
//    		RRFIFOMonitoredExtensibleMap
//    		>
//    	>
//    >
//    (3, "127.0.0.1", 4000, SOMAXCONN);
//    while(1) {}
//    delete r;
//    return 0;
}
