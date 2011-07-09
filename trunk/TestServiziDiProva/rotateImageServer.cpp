#include <iostream>
#include <fstream>
#include <exception>
#include "RotateImageServer.h"
using namespace std;

int main(int argc, char** argv)
{
	if(argc < 1)
	{
		cout << "Necessita del parametro [ip:porta] riferendosi all'indirizzo del Register.";
		return 0;
	}	
    try
	{
		RegistrableObject* r = new RegistrableSkeletonThreadPool< RegistrablePoolableCallableSkeletonWrapper<RotateImage> >(3, "127.0.0.1", 3000, SOMAXCONN);
		Publisher p(argv[1]);
		p.setPublishingMode(publish);
		p.addObjectToPublish(r);
		p();
    }
	catch(exception& e)
	{
    	cout << e.what() << endl;
	}
    return 0;
}

