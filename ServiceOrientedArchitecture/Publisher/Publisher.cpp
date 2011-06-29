#include "Publisher.h"
#include "../../SerializableObjects/SerializationStrategies/StringSerializationStrategy/StringSerializationStrategy.h"

Publisher::Publisher(string RegistryAddress) : Stub("Publisher", RegistryAddress), CallableService<Stub>("Publisher", RegistryAddress)
{
    publishingMode = publish;
    addParameter(new String(new string("publish"), false), OUT);
    bind();
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
    SerializableObjectList::iterator i = outputParameters.begin();
    for(; i != outputParameters.end(); i++)
    {
        cout << "Prova del 9:" << *((string*)((*i)->getValue())) << endl;
    }
    // new String: tanto la PointerList fa la delete
    // new string: specifico con false che non è shared, quindi può essere eliminata
}

void Publisher::operator()()
{
    //TODO addParameter(new GenericSignal, OUTIN);
    protocol();
    outputParameters.clear();
    addParameter(new String(new string(publishingModeToString(publishingMode)), false), OUT);
}
