#include "Service.h"
#include "../../SerializableObjects/DeserializationStrategies/TerminalSerializableObjectBuilder.h"
#include "../../SerializableObjects/DeserializationStrategies/SignalBuilder.h"
#include "../../SerializableObjects/SerializationStrategies/IntegerSerializationStrategy/IntegerSerializationStrategy.h"
#include "../../SerializableObjects/SerializationStrategies/RealSerializationStrategy/RealSerializationStrategy.h"
#include "../../SerializableObjects/SerializationStrategies/StringSerializationStrategy/StringSerializationStrategy.h"
#include "../../SerializableObjects/SerializationStrategies/RawByteBufferSerializationStrategy/RawByteBufferSerializationStrategy.h"
#include "../../SerializableObjects/SerializationStrategies/SignalSerializationStrategy/ParticularSignals/BadRequestSerializationStrategy/BadRequestSerializationStrategy.h"
#include "../../SerializableObjects/SerializationStrategies/SignalSerializationStrategy/ParticularSignals/GenericSignalSerializationStrategy/GenericSignalSerializationStrategy.h"
#include "../../SerializableObjects/SerializationStrategies/SignalSerializationStrategy/SignalSerializationStrategy.h"
#include "Exceptions/InvalidLengthLength.h"
#include "Exceptions/InvalidParameterListSize.h"
#include <boost/thread/thread.hpp>

Service::Service()
{
    defaultBuildersHierarchyInit();
    socket = NULL; // Il socket va inizializzato ai livelli sottostanti
}

Service::Service(string serviceIDToSet) : serviceID(serviceIDToSet)
{
    serviceID.append("()");
    defaultBuildersHierarchyInit();
    socket = NULL; // Il socket va inizializzato ai livelli sottostanti
}

Service::~Service()
{
    delete socket;
    socket = NULL;
}

void Service::defaultBuildersHierarchyInit()
{
    buildersHierarchy.addSerializableObjectBuilder(SERIALIZABLE_INTEGER, new TerminalSerializableObjectBuilder<Integer>());
    buildersHierarchy.addSerializableObjectBuilder(SERIALIZABLE_REAL, new TerminalSerializableObjectBuilder<Real>());
    buildersHierarchy.addSerializableObjectBuilder(SERIALIZABLE_STRING, new TerminalSerializableObjectBuilder<String>());
    buildersHierarchy.addSerializableObjectBuilder(SERIALIZABLE_RAW_BYTE_BUFFER, new TerminalSerializableObjectBuilder<RawByteBuffer>());
    buildersHierarchy.addSerializableObjectBuilder(SERIALIZABLE_SIGNAL, new SignalBuilder());
    buildersHierarchy[SERIALIZABLE_SIGNAL]->addSerializableObjectBuilder(SIGNAL_BAD_REQUEST, new TerminalSerializableObjectBuilder<BadRequest>());
    buildersHierarchy[SERIALIZABLE_SIGNAL]->addSerializableObjectBuilder(SIGNAL_GENERIC, new TerminalSerializableObjectBuilder<GenericSignalWrapper>());
}

void Service::sendParameters()
{
    //TODO non size_type ma qualcos'altro!
    uint32_t listSize = (uint32_t)outputParameters.size();
    socket->sendMessage(&listSize, sizeof(uint32_t));
    SerializableObjectList::iterator i = outputParameters.begin();
    void* serializedObject = NULL;
    for(; i != outputParameters.end(); i++)
    {
        uint64_t serializedObjectLength = (*i)->serialize(&serializedObject);
        socket->sendMessage(serializedObject, serializedObjectLength);
        free(serializedObject);
        serializedObject = NULL;
    }
}

SerializableObject* Service::receiveParameter()
{
    Type* receivedTypePointer = ((Type*)socket->receiveMessage(sizeof(Type)));
    Type receivedType = *receivedTypePointer;
    free(receivedTypePointer);
    int valueLengthLength = buildersHierarchy.getValueLengthLength(receivedType);
    uint64_t valueLength = 0;
    switch(valueLengthLength)
    {
    case 1: valueLengthReader<uint8_t>(valueLength); break;
    case 2: valueLengthReader<uint16_t>(valueLength); break;
    case 4: valueLengthReader<uint32_t>(valueLength); break;
    case 8: valueLengthReader<uint64_t>(valueLength); break;
    default: throw InvalidLengthLength(); break;
    }
    void* value = NULL;
    if(valueLength != 0)
    {
        value = socket->receiveMessage(valueLength);
    }
    return buildersHierarchy.delegateBuilding(receivedType, valueLength, value);
}

void Service::receiveParameters()
{
    //TODO non size_type ma qualcos'altro!
    uint32_t inputParametersSize = (uint32_t)inputParameters.size();
    uint32_t* incomingParametersSizePointer = ((uint32_t*)socket->receiveMessage(sizeof(uint32_t)));
    SerializableObjectList* incomingParameters = new SerializableObjectList;
    uint32_t incomingParametersSize = *incomingParametersSizePointer;
    free(incomingParametersSizePointer);
    if(incomingParametersSize != inputParametersSize) // Confronto del numero dei parametri.
    {
        throw InvalidParameterListSize();
    }
    for(uint32_t i = 0; i < inputParametersSize; i++)
    {
        incomingParameters->push_back(receiveParameter());
    }
    SerializableObjectList::iterator i = inputParameters.begin();
    SerializableObjectList::iterator j = incomingParameters->begin();
    try
    {
        while(i != inputParameters.end())
        {
            *(*i) = *(*j); // Confronto fra i tipi dei parametri. In caso non coincidessero viene lanciata un' eccezione.
            i++;
            j++;
        }
    }
    catch(const exception& caughtException)
    {
        delete incomingParameters;
        throw caughtException;
    }
    delete incomingParameters;
}

void Service::updateServiceID(SerializableObject* parameterToAdd, Direction parameterDirection)
{
    string directionString;
    switch(parameterDirection)
    {
    case     IN   : directionString = " IN: ";                  break;
    case     OUT  : directionString = " OUT: ";                 break;
    case     INOUT: directionString = " INOUT: ";               break;
    case     OUTIN: directionString = " OUTIN: ";               break;
    default       : directionString = " <unknown direction>: "; break;
    }
    directionString.append(parameterToAdd->getValueTypeStringRepresentation()).append(")");
    serviceID.replace(serviceID.find_last_of(')'), 1, directionString);
}
