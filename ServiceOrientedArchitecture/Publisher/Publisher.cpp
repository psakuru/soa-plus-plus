#include "Publisher.h"
#include "../../SerializableObjects/SerializationStrategies/StringSerializationStrategy/StringSerializationStrategy.h"

Publisher::Publisher(string RegistryAddress)
    : Stub("Publisher", RegistryAddress), CallableService<Stub>("Publisher", RegistryAddress)
{
    publishingMode = publish;
    addParameter(new String(new string("publish"), false), OUT);
    this->bind();
}

Publisher::~Publisher() {}

string Publisher::publishingModeToString(PublishingMode publishingModeToConvert)
{
    return (publishingModeToConvert == publish)? "publish" : "censor";
}

void Publisher::setPublishingMode(PublishingMode publishingModeToSet)
{
    publishingMode = publishingModeToSet;
    resetStatus();
}

void Publisher::bind()
{
    staticallyBind(serviceRegistryAddress);
}

void Publisher::addObjectToPublish(RegistrableObject* objectToPublish)
{
    addParameter(new String(new string(objectToPublish->getRegistrationInfo()), false), OUT);
}

void Publisher::operator()()
{
    protocol();
    resetStatus();
}

void Publisher::resetStatus()
{
	outputParameters.clear();
	serviceID = "Publisher()";
	addParameter(new String(new string(publishingModeToString(publishingMode)), false), OUT);	
}