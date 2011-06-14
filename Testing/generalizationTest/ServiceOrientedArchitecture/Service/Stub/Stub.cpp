#include "../../../SerializableObjects/DeserializationStrategies/TerminalSerializableObjectBuilder.h"
#include "../../../SerializableObjects/SerializationStrategies/IntegerSerializationStrategy/IntegerSerializationStrategy.h"
#include "../../../SerializableObjects/SerializationStrategies/RealSerializationStrategy/RealSerializationStrategy.h"
#include "../../../SerializableObjects/SerializationStrategies/StringSerializationStrategy/StringSerializationStrategy.h"
#include "../../../SerializableObjects/SerializationStrategies/RawByteBufferSerializationStrategy/RawByteBufferSerializationStrategy.h"
#include "../../../SerializableObjects/DeserializationStrategies/SignalBuilder.h"
#include "../../../SerializableObjects/SerializationStrategies/SignalSerializationStrategy/ParticularSignals/BadRequestSerializationStrategy/BadRequestSerializationStrategy.h"
#include "Stub.h"

Stub::Stub() {}

Stub::Stub(string serviceIDToSet, string serviceRegistryAddressToSet)
    : Service(serviceIDToSet)
{
    cout << "  BEGIN: Stub.Stub(string serviceIDToSet, string serviceRegistryAddressToSet)" << endl;
    cout << "  Passati i parametri ricevuti al costruttore di Service" << endl;
    serviceRegistryAddress = serviceRegistryAddressToSet;
    cout << "  Settato il serviceRegistry" << endl;
    bind();
    cout << "  END: Stub.Stub(string serviceIDToSet, string serviceRegistryAddressToSet)" << endl;
}

Stub::~Stub() {}

string Stub::getServiceRegistryAddress()
{
    return serviceRegistryAddress;
}

string Stub::setServiceRegistryAddress(string serviceRegistryAddressToSet)
{
    serviceRegistryAddress = serviceRegistryAddressToSet;
}

void Stub::rebind()
{
    cout << "REBind dello stub!" << endl;
    bind();
}

void Stub::bind()
{
    cout << "  BEGIN: Stub.bind()" << endl;
    cout << "  BEGIN: Stub.bind()" << endl;
}

void Stub::staticallyBind(string serviceProviderAddressToSet)
{
    serviceProviderAddress = serviceProviderAddressToSet;
    //TODO metodino (?) per il parsing degli indirizzi
    string ipAddress = serviceProviderAddress.substr(0, serviceProviderAddress.find_first_of(':'));
    string portString = serviceProviderAddress.substr(serviceProviderAddress.find_first_of(':')+1);
    int port = atoi(portString.c_str());
    //TODO check: e se il socket era stato inizializzato?
    socket = new TcpIpActiveSocket(ipAddress, port);
}

void Stub::protocol()
{
    SerializableObjectList::iterator i = inputParameters.begin();
    for(; i != inputParameters.end(); i++) outputParameters.push_back(&(*i));
    sendParameters();
    receiveParameters();
}
