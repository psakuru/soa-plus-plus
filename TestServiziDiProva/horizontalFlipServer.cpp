#include <iostream>
#include <fstream>
#include <exception>
#include "HorizontalFlipImageServer.h"
#include <string>
using namespace std;

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		cout << "Necessita del parametro [ip:porta] riferendosi all'indirizzo del Register.";
		return 0;
	}
	try
	{
		RegistrableSkeletonThreadPool< RegistrablePoolableCallableSkeletonWrapper<HorizontalFlipImage> >*
		serviceThreadPool =
		new RegistrableSkeletonThreadPool< RegistrablePoolableCallableSkeletonWrapper<HorizontalFlipImage> >
		(3, "127.0.0.1", 3001, SOMAXCONN);
		Publisher servicePublisher(argv[1]);
		servicePublisher.setPublishingMode(publish);
		servicePublisher.addObjectToPublish(serviceThreadPool);
		servicePublisher();
		string shutdown;
		while(shutdown.compare("shutdown") != 0) cin >> shutdown;
		delete serviceThreadPool; //Graceful shutdown
    }
	catch(exception& e)
	{
    	cout << e.what() << endl;
	}
    return 0;
}

