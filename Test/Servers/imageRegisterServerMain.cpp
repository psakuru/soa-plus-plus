#include <iostream>
#include <exception>
#include "../../ServiceOrientedArchitecture/Service/Skeleton/RegistrablePoolableCyclicCallableSkeleton/RegistrablePoolableCyclicCallableSkeleton.h"
#include "../../ServiceOrientedArchitecture/Service/Skeleton/Utilities/PoolableCallableSkeletonWrappers/RegistrablePoolableCallableSkeletonWrapper/RegistrablePoolableCallableSkeletonWrapper.h"
#include "../../ServiceOrientedArchitecture/Service/Skeleton/SkeletonThreadPool/RegistrableSkeletonThreadPool/RegistrableSkeletonThreadPool.h"
#include "../../ServiceOrientedArchitecture/Publisher/Publisher.h"
#include "../../ObjectInterfaces/RegistrableObject/RegistrableObject.h"
#include "StoreImageServer.h"
#include "GetImageServer.h"
#include "GetListServer.h"
#include <boost/lexical_cast.hpp>
using namespace std;

int main(int argc, char** argv)
{
	if(argc < 5)
	{
		cout << "Usage: imageRegisterServer <thread_pools_size> <listening_IP> <listening_base_port> <registerIP:registerPort>" << endl;
		return 1;
	}
	try
	{
	    /* Pools di thread. Per semplicità ascoltano su porte consecutive e hanno la stessa dimensione del pool.
         * per il caso generale è sufficiente aggiungere più parametri in argv
         */
		RegistrableObject* imageStorer =
		new RegistrableSkeletonThreadPool< RegistrablePoolableCallableSkeletonWrapper< StoreImageServer > >
        (boost::lexical_cast<int>(argv[1]), argv[2], boost::lexical_cast<int>(argv[3]), SOMAXCONN);
		RegistrableObject* imageGetter =
		new RegistrableSkeletonThreadPool< RegistrablePoolableCallableSkeletonWrapper< GetImageServer > >
		(boost::lexical_cast<int>(argv[1]), argv[2], (boost::lexical_cast<int>(argv[3]))+1, SOMAXCONN);
		RegistrableObject* imageListGetter =
		new RegistrableSkeletonThreadPool< RegistrablePoolableCallableSkeletonWrapper< GetListServer > >
		(boost::lexical_cast<int>(argv[1]), argv[2], (boost::lexical_cast<int>(argv[3]))+2, SOMAXCONN);
		/* Publisher */
		Publisher servicePublisher(argv[4]);
		servicePublisher.setPublishingMode(publish);
		servicePublisher.addObjectToPublish(imageStorer);
		servicePublisher.addObjectToPublish(imageGetter);
		servicePublisher.addObjectToPublish(imageListGetter);
		/* Pubblicazione */
		servicePublisher();
		/* Graceful shutdown sequence */
		string shutdown;
		while(shutdown.compare("shutdown") != 0) cin >> shutdown; // Attesa del comando
		servicePublisher.setPublishingMode(censor); // Modalità di publishing: deregistrazione
		servicePublisher.addObjectToPublish(imageStorer);
		servicePublisher.addObjectToPublish(imageGetter);
		servicePublisher.addObjectToPublish(imageListGetter);
		servicePublisher(); // Deregistrazione
		delete imageStorer; //Graceful shutdown
		delete imageGetter;
		delete imageListGetter;
    }
	catch(exception& caughtException)
	{
    	cout << caughtException.what() << endl;
    	return 1;
	}
    return 0;
}

