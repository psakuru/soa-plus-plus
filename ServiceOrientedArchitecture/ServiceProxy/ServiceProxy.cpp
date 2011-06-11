#include "ServiceProxy.h"
#include "../../SerializableObjects/ParticularSerializableObjects/TerminalSerializableObjectBuilder.h"
#include "../../SerializableObjects/ParticularSerializableObjects/Integer/Integer.h"
#include "../../SerializableObjects/ParticularSerializableObjects/Real/Real.h"
#include "../../SerializableObjects/ParticularSerializableObjects/String/String.h"
#include "../../SerializableObjects/ParticularSerializableObjects/RawByteBuffer/RawByteBuffer.h"
#include "../../SerializableObjects/ParticularSerializableObjects/Signal/Signal.h"
#include "../../SerializableObjects/ParticularSerializableObjects/Signal/SignalBuilder.h"
#include "../../SerializableObjects/ParticularSerializableObjects/Signal/ParticularSignals/BadRequest/BadRequest.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

ServiceProxy::ServiceProxy()
{
    defaultBuildersHierarchyInit();
    socket = NULL;
}

ServiceProxy::ServiceProxy(string serviceIDToSet, string serviceRegistryAddressToSet)
: serviceID(serviceIDToSet), serviceRegistryAddress(serviceRegistryAddressToSet)
{
    defaultBuildersHierarchyInit();
    bindProxy(); //Inizializza il socket e lo fa connettere
}

void ServiceProxy::defaultBuildersHierarchyInit()
{
    buildersHierarchy.addSerializableObjectBuilder(SERIALIZABLE_INTEGER, new TerminalSerializableObjectBuilder<Integer>());
    buildersHierarchy.addSerializableObjectBuilder(SERIALIZABLE_REAL, new TerminalSerializableObjectBuilder<Real>());
    buildersHierarchy.addSerializableObjectBuilder(SERIALIZABLE_STRING, new TerminalSerializableObjectBuilder<String>());
    buildersHierarchy.addSerializableObjectBuilder(SERIALIZABLE_RAW_BYTE_BUFFER, new TerminalSerializableObjectBuilder<RawByteBuffer>());
    buildersHierarchy.addSerializableObjectBuilder(SERIALIZABLE_SIGNAL, new SignalBuilder());
    buildersHierarchy[SERIALIZABLE_SIGNAL]->addSerializableObjectBuilder(SIGNAL_BAD_REQUEST, new TerminalSerializableObjectBuilder<BadRequest>());
    //TODO altri segnali
}

ServiceProxy::~ServiceProxy()
{
    //dtor
}

void ServiceProxy::sendParameters(list<SerializableObject*> parameterList)
{
    list<SerializableObject*>::size_type listSize = parameterList.size();
    socket->sendMessage(&listSize, sizeof(list<SerializableObject*>::size_type));
    list<SerializableObject*>::iterator i = parameterList.begin();
    void* serializedObject = NULL;
    for(; i != parameterList.end(); i++)
    {
        uint64_t serializedObjectLength = (*i)->serialize(&serializedObject);
        socket->sendMessage(serializedObject, serializedObjectLength);
        free(serializedObject);
        serializedObject = NULL;
    }
}

SerializableObject* ServiceProxy::receiveResponseParameter()
{
    //TODO trovare un modo per fare la receive senza stare a fare la free del puntatore
    Type* receivedTypePointer = ((Type*)socket->receiveMessage(sizeof(Type)));
    Type receivedType = *receivedTypePointer;
    cout << "Tipo ricevuto: " << receivedType << endl;
    free(receivedTypePointer);
    //OK??
    int valueLengthLength = buildersHierarchy.getValueLengthLength(receivedType);
    cout << "Lunghezza del campo length da ricevere: " << valueLengthLength << endl;
    uint64_t valueLength =
        (valueLengthLength == 0)? 0:
        (valueLengthLength == sizeof(uint8_t ))? *((uint8_t*)socket->receiveMessage(sizeof(uint8_t))) :
        (valueLengthLength == sizeof(uint16_t))? *((uint16_t*)socket->receiveMessage(sizeof(uint16_t))) :
        (valueLengthLength == sizeof(uint32_t))? *((uint32_t*)socket->receiveMessage(sizeof(uint32_t))) :
        (valueLengthLength == sizeof(uint64_t))? *((uint64_t*)socket->receiveMessage(sizeof(uint64_t))) : 0;
    cout << "Campo length: " << valueLength << endl;
    void* value = (valueLength == 0)? NULL : socket->receiveMessage(valueLength);
    return buildersHierarchy.delegateBuilding(receivedType, valueLength, value); //NB: la guild deve fare la free del value
}

list<SerializableObject*>* ServiceProxy::receiveResponseParameters()
{
    list<SerializableObject*>* responseParameters = new list<SerializableObject*>;
    list<SerializableObject*>::size_type outputListSize = outputParameters.size();
    for(int i = 0; i < outputListSize; i++)
    {
        //TODO controllo sul tipo ritornato dal server!
        responseParameters->push_back(receiveResponseParameter());
    }
    return responseParameters; //Ritorno per puntatore!
}

void ServiceProxy::doService()
{
    sendParameters(inputParameters);
    sendParameters(outputParameters);
    list<SerializableObject*>* valuesToReturn = receiveResponseParameters();
    list<SerializableObject*>::iterator i = valuesToReturn->begin();
    cout << "Cosa mi è arrivato: " << (*i)->getType() << endl;
    list<SerializableObject*>::iterator j = outputParameters.begin();
    //TODO eccezione: liste con diverso numero di parametri ecc...
    while(i != valuesToReturn->end())
    {
        *(*j) = *(*i);
        i++;
        j++;
    }
    //delete valuesToReturn;
}

string ServiceProxy::getServiceRegistryAddress()
{
    return serviceRegistryAddress;
}

string ServiceProxy::setServiceRegistryAddress(string serviceRegistryAddressToSet)
{
    serviceRegistryAddress = serviceRegistryAddressToSet;
}

void ServiceProxy::bindProxy()
{
    //TODO chiedere al serviceRegistry l' indirizzo e porta del serviceProvider che offre il service
    //TODO effettua la connessione verso il serviceProvider
}

void ServiceProxy::staticallyBindProxy(string serviceProviderAddressToSet)
{
    cout << "staticallyBind(" << serviceProviderAddressToSet << ")" << endl;
    serviceProviderAddress = serviceProviderAddressToSet;
    //TODO metodino (?) per il parsing degli indirizzi
    string ipAddress = serviceProviderAddress.substr(0, serviceProviderAddress.find_first_of(':'));
    cout << "ipAddress: " << ipAddress << endl;
    string portString = serviceProviderAddress.substr(serviceProviderAddress.find_first_of(':')+1);
    cout << "portString: " << portString << endl;
    int port = atoi(portString.c_str());
    cout << "port: " << port << endl;
    //TODO check: e se il socket era stato inizializzato?
    socket = new TcpIpActiveSocket(ipAddress, port);
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
