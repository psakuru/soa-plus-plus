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
    outputParameters.clear();
    addParameter(new String(new string(publishingModeToString(publishingMode)), false), OUT);
}

void Publisher::bind()
{
    staticallyBind(serviceRegistryAddress);
}

void Publisher::addObjectToPublish(RegistrableObject* objectToPublish)
{
    addParameter(new String(new string(objectToPublish->getRegistrationInfo()), false), OUT);
    // new String: tanto la PointerList fa la delete
    // new string: specifico con false che non è shared, quindi può essere eliminata
}

void Publisher::operator()()
{
    protocol();
    outputParameters.clear();
    addParameter(new String(new string(publishingModeToString(publishingMode)), false), OUT); //nasconde al programmatore che in realtà la modalità è una stringa come le altre da aggiungere nei parametri
}
