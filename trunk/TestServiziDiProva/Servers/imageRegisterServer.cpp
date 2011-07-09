#include <iostream>
#include <fstream>
#include <exception>
#include "../ServiceOrientedArchitecture/Service/Skeleton/RegistrablePoolableCyclicCallableSkeleton/RegistrablePoolableCyclicCallableSkeleton.h"
#include "../ServiceOrientedArchitecture/Service/Skeleton/Utilities/PoolableCallableSkeletonWrappers/RegistrablePoolableCallableSkeletonWrapper/RegistrablePoolableCallableSkeletonWrapper.h"
#include "../ServiceOrientedArchitecture/Service/Skeleton/SkeletonThreadPool/RegistrableSkeletonThreadPool/RegistrableSkeletonThreadPool.h"
#include "../ServiceOrientedArchitecture/Publisher/Publisher.h"
#include "../ObjectInterfaces/RegistrableObject/RegistrableObject.h"
#include "StoreImageServer.h"
#include "GetImageServer.h"
#include "GetListServer.h"
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
		RegistrableObject* r = new RegistrableSkeletonThreadPool< RegistrablePoolableCallableSkeletonWrapper<StoreImage> >(3, "127.0.0.1", 5000, SOMAXCONN);
		RegistrableObject* s = new RegistrableSkeletonThreadPool< RegistrablePoolableCallableSkeletonWrapper<GetImage> >(3, "127.0.0.1", 5001, SOMAXCONN);
		RegistrableObject* t = new RegistrableSkeletonThreadPool< RegistrablePoolableCallableSkeletonWrapper<GetList> >(3, "127.0.0.1", 5002, SOMAXCONN);
		Publisher p(argv[1]);
		p.setPublishingMode(publish);
		p.addObjectToPublish(r);
		p.addObjectToPublish(s);
		p.addObjectToPublish(t);
		p();
    }
	catch(exception& e)
	{
    	cout << e.what() << endl;
	}
    return 0;
}

