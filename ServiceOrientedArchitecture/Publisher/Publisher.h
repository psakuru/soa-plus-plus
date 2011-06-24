#ifndef SERVICEPUBLISHER_H
#define SERVICEPUBLISHER_H

#include "../Service/CallableService/CallableService.h"
#include "../Service/Stub/Stub.h"
#include "../../ObjectInterfaces/RegistrableObject/RegistrableObject.h"
#include <string>
using namespace std;

class Publisher : public CallableService<Stub>
{
    public:
        Publisher(string RegistryAddress);
        virtual ~Publisher();
        void addObjectToPublish(RegistrableObject* objectToPublish);
        void operator()();
};

#endif // SERVICEPUBLISHER_H
