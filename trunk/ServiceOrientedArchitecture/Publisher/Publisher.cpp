#include "Publisher.h"
#include "../../SerializableObjects/SerializationStrategies/StringSerializationStrategy/StringSerializationStrategy.h"

Publisher::Publisher(string RegistryAddress) : Stub("Publisher", RegistryAddress), CallableService<Stub>("Publisher", RegistryAddress)
{
    addParameter(new String(new string("publish"), false), OUT);
}

Publisher::~Publisher() {}

void Publisher::bind()
{
    staticallyBind(serviceRegistryAddress);
}

void Publisher::addObjectToPublish(RegistrableObject* objectToPublish)
{
    addParameter(new String(new string(objectToPublish->getRegistrationInfo()), false), OUT);
    cout << "Prova del 9:" << *((string*)((*(outputParameters.begin()))->getValue())) << endl;
    // new String: tanto la PointerList fa la delete
    // new string: specifico con false che non è shared, quindi può essere eliminata
}

void Publisher::operator()()
{
    //TODO addParameter(new GenericSignal, OUTIN);
    protocol();
    outputList.clear();
    addParameter(new String(new string("publish"), false), OUT);
}
