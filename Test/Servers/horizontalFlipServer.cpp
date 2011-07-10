#include <iostream>
#include <fstream>
#include <exception>
#include "HorizontalFlipImageServer.h"
#include <string>
#include <boost/lexical_cast.hpp>
using namespace std;

int main(int argc, char** argv)
{
	if(argc < 5)
	{
		cout << "Usage: register <thread_pool_size> <listening_IP> <listening_port> <registerIP:registerPort>";
		return 1;
	}
	try
	{
	    /* Pool di thread */
		RegistrableSkeletonThreadPool< RegistrablePoolableCallableSkeletonWrapper<HorizontalFlipImage> >*
		serviceThreadPool =
		new RegistrableSkeletonThreadPool< RegistrablePoolableCallableSkeletonWrapper<HorizontalFlipImage> >
		(boost::lexical_cast<int>(argv[1]), argv[2], boost::lexical_cast<int>(argv[3]), SOMAXCONN);
		/* Publisher */
		Publisher servicePublisher(argv[4]);
		servicePublisher.setPublishingMode(publish);
		servicePublisher.addObjectToPublish(serviceThreadPool);
		/* Pubblicazione */
		servicePublisher();
		/* Graceful shutdown sequence */
		string shutdown;
		while(shutdown.compare("shutdown") != 0) cin >> shutdown; // Attesa del comando
		servicePublisher.setPublishingMode(censor); // Modalità di publishing: deregistrazione
		servicePublisher.addObjectToPublish(serviceThreadPool);
		servicePublisher(); // Deregistrazione
		delete serviceThreadPool; //Graceful shutdown
    }
	catch(exception& e)
	{
    	cout << e.what() << endl;
	}
    return 0;
}

