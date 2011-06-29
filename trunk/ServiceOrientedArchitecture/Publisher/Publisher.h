#ifndef SERVICEPUBLISHER_H
#define SERVICEPUBLISHER_H

#include "../Service/CallableService/CallableService.h"
#include "../Service/Stub/Stub.h"
#include "../../ObjectInterfaces/RegistrableObject/RegistrableObject.h"
#include <string>
using namespace std;

enum PublishingMode {publish, censor};

class Publisher : public CallableService<Stub>
{
    protected:
        PublishingMode publishingMode;
        void bind();
        string publishingModeToString(PublishingMode publishingModeToConvert);
    public:
        Publisher(string RegistryAddress);
        virtual ~Publisher();
        void setPublishingMode(PublishingMode publishingModeToSet);
        void addObjectToPublish(RegistrableObject* objectToPublish);
        void operator()();
};

#endif // SERVICEPUBLISHER_H
