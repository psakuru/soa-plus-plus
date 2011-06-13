#include "../../../SerializableObjects/DeserializationStrategies/TerminalSerializableObjectBuilder.h"
#include "../../../SerializableObjects/SerializationStrategies/IntegerSerializationStrategy/IntegerSerializationStrategy.h"
#include "../../../SerializableObjects/SerializationStrategies/RealSerializationStrategy/RealSerializationStrategy.h"
#include "../../../SerializableObjects/SerializationStrategies/StringSerializationStrategy/StringSerializationStrategy.h"
#include "../../../SerializableObjects/SerializationStrategies/RawByteBufferSerializationStrategy/RawByteBufferSerializationStrategy.h"
#include "../../../SerializableObjects/DeserializationStrategies/SignalBuilder.h"
#include "../../../SerializableObjects/SerializationStrategies/SignalSerializationStrategy/ParticularSignals/BadRequestSerializationStrategy/BadRequestSerializationStrategy.h"
#include "ServiceProxy.h"

ServiceProxy::ServiceProxy()
{
    //ctor
}

ServiceProxy::ServiceProxy(string serviceIDToSet, string serviceRegistryAddressToSet)
: Service(serviceIDToSet, serviceRegistryAddressToSet){}

ServiceProxy::~ServiceProxy()
{
    //dtor
}

void ServiceProxy::bind()
{
    //Da fare
}

void ServiceProxy::staticallyBind(string serviceProviderAddressToSet)
{
    serviceProviderAddress = serviceProviderAddressToSet;
    //TODO metodino (?) per il parsing degli indirizzi
    string ipAddress = serviceProviderAddress.substr(0, serviceProviderAddress.find_first_of(':'));
    string portString = serviceProviderAddress.substr(serviceProviderAddress.find_first_of(':')+1);
    int port = atoi(portString.c_str());
    //TODO check: e se il socket era stato inizializzato?
    socket = new TcpIpActiveSocket(ipAddress, port);
}

void ServiceProxy::doService()
{
    sendParameters();
    receiveParameters();
}

void ServiceProxy::operator<<(int& value)
{
    SerializableObject* objectToPushIntoList = new Integer(value);
    inputParameters.push_back(objectToPushIntoList);
}

void ServiceProxy::operator<<(double& value)
{
    SerializableObject* objectToPushIntoList = new Real(value);
    inputParameters.push_back(objectToPushIntoList);
}

void ServiceProxy::operator<<(string& value)
{
    SerializableObject* objectToPushIntoList = new String(value);
    inputParameters.push_back(objectToPushIntoList);
}
void ServiceProxy::operator<<(ByteArray& value)
{
    SerializableObject* objectToPushIntoList = new RawByteBuffer(value);
    inputParameters.push_back(objectToPushIntoList);
}

void ServiceProxy::operator<<(BadRequestSignal& value)
{
    SerializableObject* objectToPushIntoList = new BadRequest(value);
    inputParameters.push_back(objectToPushIntoList);
}

void ServiceProxy::operator>>(int& value)
{
    SerializableObject* objectToPushIntoList = new Integer(value);
    outputParameters.push_back(objectToPushIntoList);
}

void ServiceProxy::operator>>(double& value)
{
    SerializableObject* objectToPushIntoList = new Real(value);
    outputParameters.push_back(objectToPushIntoList);
}

void ServiceProxy::operator>>(string& value)
{
    SerializableObject* objectToPushIntoList = new String(value);
    outputParameters.push_back(objectToPushIntoList);
}
void ServiceProxy::operator>>(ByteArray& value)
{
    SerializableObject* objectToPushIntoList = new RawByteBuffer(value);
    outputParameters.push_back(objectToPushIntoList);

}

void ServiceProxy::operator>>(BadRequestSignal& value)
{
    cout << "operator<< : wrapping del BadRequestSignal" << endl;
    SerializableObject* objectToPushIntoList = new BadRequest(value);
    outputParameters.push_back(objectToPushIntoList);
    cout << "BadRequestSignal wrappato in BadRequestSerializationStrategy e inserito nella lista out" << endl;
}
