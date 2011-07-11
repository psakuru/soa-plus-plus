#include <iostream>
#include <fstream>
#include <exception>
#include "HorizontalFlipImageServer.h"
#include <string>
#include <boost/lexical_cast.hpp>
#include "../../ObjectInterfaces/RegistrableObject/RegistrableObject.h"
#include "../../ServiceOrientedArchitecture/Service/Skeleton/SkeletonThreadPool/RegistrableSkeletonThreadPool/RegistrableSkeletonThreadPool.h"
#include "../../ServiceOrientedArchitecture/Service/Skeleton/Utilities/PoolableCallableSkeletonWrappers/RegistrablePoolableCallableSkeletonWrapper/RegistrablePoolableCallableSkeletonWrapper.h"
#include "../../ServiceOrientedArchitecture/Publisher/Publisher.h"
using namespace std;

int main(int argc, char** argv)
{
	if(argc < 5)
	{
		cout << "Usage: horizontalFlipServer <thread_pool_size> <listening_IP> <listening_port> <registerIP:registerPort>" << endl;
		return 1;
	}
	try
	{
	    /* Pool di thread */
		RegistrableObject* serviceThreadPool =
		new RegistrableSkeletonThreadPool< RegistrablePoolableCallableSkeletonWrapper<HorizontalFlipImage> >
		(boost::lexical_cast<int>(argv[1]), argv[2], boost::lexical_cast<int>(argv[3]), SOMAXCONN);
		/* Publisher */
		Publisher servicePublisher(argv[4]);
		servicePublisher.setPublishingMode(publish);
		servicePublisher.addObjectToPublish(serviceThreadPool);
		/* Pubblicazione */
		try
		{
		    servicePublisher(); // Registrazione
		}
		catch(const exception& caughtException)
		{
		    cout << "Publishing problem" << endl; //Il servizio é stato attivato ma non è pubblicato
		}
		/* Graceful shutdown sequence */
		string shutdown;
		while(shutdown.compare("shutdown") != 0) cin >> shutdown; // Attesa del comando
		servicePublisher.setPublishingMode(censor); // Modalità di publishing: deregistrazione
		servicePublisher.addObjectToPublish(serviceThreadPool);
		try
		{
		    servicePublisher(); // Deregistrazione
		}
		catch(const exception& caughtException)
		{
		    delete serviceThreadPool; //Graceful shutdown
		    throw caughtException;
		}
		delete serviceThreadPool; //Graceful shutdown
    }
	catch(const exception& caughtException)
	{
    	cout << caughtException.what() << endl;
    	return 1;
	}
    return 0;
}

