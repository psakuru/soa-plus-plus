#include "ServiceProxy.h"

ServiceProxy::ServiceProxy(string serviceIDToSet, string serviceRegistryAddressToSet)
    : serviceID(serviceIDToSet), serviceRegistryAddress(serviceRegistryAddressToSet)
{
    buildersHierarchy.addSerializableObjectBuilder(SERIALIZABLE_INTEGER, new TerminalSerializableObjectBuilder<Integer>());
    buildersHierarchy.addSerializableObjectBuilder(SERIALIZABLE_REAL, new TerminalSerializableObjectBuilder<Real>());
    buildersHierarchy.addSerializableObjectBuilder(SERIALIZABLE_STRING, new TerminalSerializableObjectBuilder<String>());
    buildersHierarchy.addSerializableObjectBuilder(SERIALIZABLE_RAW_BYTE_BUFFER, new TerminalSerializableObjectBuilder<RawByteBuffer>());
    buildersHierarchy.addSerializableObjectBuilder(SERIALIZABLE_SIGNAL, new SignalBuilder());
    buildersHierarchy[SERIALIZABLE_SIGNAL].addSerializableObjectBuilder(SIGNAL_BAD_REQUEST, new TerminalSerializableObjectBuilder<BadRequest>());
    //TODO altri segnali
    bindProxy();
}

ServiceProxy::~ServiceProxy()
{
    //dtor
}

void ServiceProxy::sendParameters(list<SerializableObject*> parameterList)
{
    list<SerializableObject*>::size_type listSize = parameterList.size();
    socket.sendMessage(&listSize, sizeof(list<SerializableObject*>::size_type));
    list<SerializableObject*>::iterator i = parameterList.begin();
    void* serializedObject = NULL;
    for(; i != parameterList.end(); i++)
    {
        uint64_t serializedObjectLength = (*i).serialize(&serializedObject);
        socket.sendMessage(serializedObject, serializedObjectLength);
        free(serializedObject);
        serializedObject = NULL;
    }
}

SerializableObject* ServiceProxy::receiveResponseParameter()
{
    //TODO trovare un modo per fare la receive senza stare a fare la free del puntatore
    Type* receivedTypePointer = ((Type*)socket.receiveMessage(sizeof(Type)));
    Type receivedType = *receivedTypePointer;
    free(receivedTypePointer);
    //OK??
    int valueLengthLength = buildersHierarcy.getValueLengthLength(receivedType);
    uint64_t valueLength =
        (valueLengthLength == 0)? 0:
        (valueLengthLength == sizeof(uint8_t ))? *((uint8_t*)socket.receiveMessage(sizeof(uint8_t))) :
        (valueLengthLength == sizeof(uint16_t))? *((uint16_t*)socket.receiveMessage(sizeof(uint16_t))) :
        (valueLengthLength == sizeof(uint32_t))? *((uint32_t*)socket.receiveMessage(sizeof(uint32_t))) :
        (valueLengthLength == sizeof(uint64_t))? *((uint64_t*)socket.receiveMessage(sizeof(uint64_t)));
    void* value = (valueLength == 0)? NULL : socket.receiveMessage(valueLength);
    return buildersHierarchy.delegateWork(receivedType, valueLength, value); //NB: la guild deve fare la free del value
}

list<SerializableObject*>* ServiceProxy::receiveResponseParameters()
{
    list<SerializableObject*>* responseParameters = new list<SerializableObject*>;
    list<SerializableObject*>::size_type outputListSize = outputParameters.size();
    for(int i = 0; i < outputListSize; i++)
    {
        responseParameters->push_back(receiveResponseParameter());
    }
    return responseParameters; //Ritorno per puntatore!
}

void ServiceProxy::doService()
{
    sendParameters(inputParameters);
    sendParameters(outputParameters);
    list<SerializableObject*> valuesToReturn = receiveResponseParameters();
    list<SerializableObject*>::iterator i = valuesToReturn.begin();
    list<SerializableObject*>::iterator j = outputParameters.begin();
    //TODO eccezione: liste con diverso numero di parametri ecc...
    while(i != valuesToReturn.end())
    {
        *(*j) = *(*i);
        i++;
        j++;
    }
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

void staticallyBindProxy(string serviceProviderAddressToSet)
{
    //TODO effettua la connessione verso il serviceProvider settando tutto opportunamente
}

