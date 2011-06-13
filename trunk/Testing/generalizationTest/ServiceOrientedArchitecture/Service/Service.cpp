#include "Service.h"
#include "../../SerializableObjects/DeserializationStrategies/TerminalSerializableObjectBuilder.h"
#include "../../SerializableObjects/DeserializationStrategies/SignalBuilder.h"
#include "../../../SerializableObjects/SerializationStrategies/IntegerSerializationStrategy/IntegerSerializationStrategy.h"
#include "../../../SerializableObjects/SerializationStrategies/RealSerializationStrategy/RealSerializationStrategy.h"
#include "../../../SerializableObjects/SerializationStrategies/StringSerializationStrategy/StringSerializationStrategy.h"
#include "../../../SerializableObjects/SerializationStrategies/RawByteBufferSerializationStrategy/RawByteBufferSerializationStrategy.h"
#include "../../../SerializableObjects/SerializationStrategies/SignalSerializationStrategy/ParticularSignals/BadRequestSerializationStrategy/BadRequestSerializationStrategy.h"
#include "../../../SerializableObjects/SerializationStrategies/SignalSerializationStrategy/SignalSerializationStrategy.h"

Service::Service()
{
    defaultBuildersHierarchyInit();
    socket = NULL;
}

Service::Service(string serviceIDToSet, string serviceRegistryAddressToSet)
    : serviceID(serviceIDToSet), serviceRegistryAddress(serviceRegistryAddressToSet)
{
    defaultBuildersHierarchyInit();
    this->bind(); //Inizializza il socket e lo fa connettere
}

void Service::bind(){}

void Service::defaultBuildersHierarchyInit()
{
    buildersHierarchy.addSerializableObjectBuilder(SERIALIZABLE_INTEGER, new TerminalSerializableObjectBuilder<Integer>());
    buildersHierarchy.addSerializableObjectBuilder(SERIALIZABLE_REAL, new TerminalSerializableObjectBuilder<Real>());
    buildersHierarchy.addSerializableObjectBuilder(SERIALIZABLE_STRING, new TerminalSerializableObjectBuilder<String>());
    buildersHierarchy.addSerializableObjectBuilder(SERIALIZABLE_RAW_BYTE_BUFFER, new TerminalSerializableObjectBuilder<RawByteBuffer>());
    buildersHierarchy.addSerializableObjectBuilder(SERIALIZABLE_SIGNAL, new SignalBuilder());
    buildersHierarchy[SERIALIZABLE_SIGNAL]->addSerializableObjectBuilder(SIGNAL_BAD_REQUEST, new TerminalSerializableObjectBuilder<BadRequest>());
}

void Service::sendParameters()
{
    SerializableObjectList::size_type listSize = outputParameters.size();
    socket->sendMessage(&listSize, sizeof(SerializableObjectList::size_type));
    SerializableObjectList::iterator i = outputParameters.begin();
    void* serializedObject = NULL;
    for(; i != outputParameters.end(); i++)
    {
        uint64_t serializedObjectLength = (*i).serialize(&serializedObject);
        socket->sendMessage(serializedObject, serializedObjectLength);
        free(serializedObject);
        serializedObject = NULL;
    }
}

SerializableObject* Service::receiveParameter()
{
    //TODO trovare un modo per fare la receive senza stare a fare la free del puntatore
    Type* receivedTypePointer = ((Type*)socket->receiveMessage(sizeof(Type)));
    Type receivedType = *receivedTypePointer;
    free(receivedTypePointer);
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

void Service::receiveParameters()
{
    SerializableObjectList* incomingParameters = new SerializableObjectList;
    SerializableObjectList::size_type inputParametersSize = inputParameters.size();
    SerializableObjectList::size_type* incomingParametersSizePointer =
        ((SerializableObjectList::size_type*)socket->receiveMessage(sizeof(SerializableObjectList::size_type)));
    SerializableObjectList::size_type incomingParametersSize = *incomingParametersSizePointer;
    free(incomingParametersSizePointer);
    if(incomingParametersSize != inputParametersSize)
    {
        /*throw exception!*/
    }
    for(int i = 0; i < inputParametersSize; i++)
    {
        //TODO controllo sul tipo ritornato dal server!
        incomingParameters->push_back(receiveParameter());
    }
    SerializableObjectList::iterator i = inputParameters.begin();
    SerializableObjectList::iterator j = incomingParameters->begin();
    while(i != inputParameters.end())
    {
        (*i) = (*j);
        i++;
        j++;
    }
    delete incomingParameters;
}

string Service::getServiceRegistryAddress()
{
    return serviceRegistryAddress;
}

string Service::setServiceRegistryAddress(string serviceRegistryAddressToSet)
{
    serviceRegistryAddress = serviceRegistryAddressToSet;
}
