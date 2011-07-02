#include "Service.h"
#include "../../SerializableObjects/DeserializationStrategies/TerminalSerializableObjectBuilder.h"
#include "../../SerializableObjects/DeserializationStrategies/SignalBuilder.h"
#include "../../SerializableObjects/SerializationStrategies/IntegerSerializationStrategy/IntegerSerializationStrategy.h"
#include "../../SerializableObjects/SerializationStrategies/RealSerializationStrategy/RealSerializationStrategy.h"
#include "../../SerializableObjects/SerializationStrategies/StringSerializationStrategy/StringSerializationStrategy.h"
#include "../../SerializableObjects/SerializationStrategies/RawByteBufferSerializationStrategy/RawByteBufferSerializationStrategy.h"
#include "../../SerializableObjects/SerializationStrategies/SignalSerializationStrategy/ParticularSignals/BadRequestSerializationStrategy/BadRequestSerializationStrategy.h"
#include "../../SerializableObjects/SerializationStrategies/SignalSerializationStrategy/SignalSerializationStrategy.h"
#include <boost/thread/thread.hpp>

Service::Service()
{


    cout << "Cool!" << endl;
    defaultBuildersHierarchyInit();
    socket = NULL; //Il socket va inizializzato ai livelli sottostanti


}

Service::Service(string serviceIDToSet) : serviceID(serviceIDToSet)
{





    serviceID.append("()");
    cout << "ServiceID corrente: " << serviceID << endl;
    cout << "Vingilioth:::: vengo richiamato io, maremma cane! serviceID: " << serviceID << " this:" << hex << (void*)this << dec << endl;
    defaultBuildersHierarchyInit();

    socket = NULL; //Il socket va inizializzato ai livelli sottostanti


}

Service::~Service()
{


    delete socket;
    socket = NULL;


}

void Service::defaultBuildersHierarchyInit()
{
    cout << "TID:" << boost::this_thread::get_id() << " Service::defaultBuildersHierarchyInit()" << endl << endl;


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
    cout << "Tipo ricevuto: " << receivedType << endl;
    free(receivedTypePointer);
    int valueLengthLength = buildersHierarchy.getValueLengthLength(receivedType);
    uint64_t valueLength = 0;
    switch(valueLengthLength)
    {
        //TODO templatizzare questo switch o comunque trovare un modo per non ripetere il codice
    case 0:
        //TODO throw exception?
        break;
    case 1: //TODO mettere delle define da qualche parte per i sizeof! E usarla qui al posto di 1!
    {
        uint8_t* valueLengthPointer8bit = (uint8_t*)socket->receiveMessage(sizeof(uint8_t));
        valueLength = *valueLengthPointer8bit;
        free(valueLengthPointer8bit);
    }
    break;
    case 2: //TODO mettere delle define da qualche parte per i sizeof! E usarla qui al posto di 2!
    {
        uint16_t* valueLengthPointer16bit = (uint16_t*)socket->receiveMessage(sizeof(uint16_t));
        valueLength = *valueLengthPointer16bit;
        free(valueLengthPointer16bit);
    }
    break;
    case 4: //TODO mettere delle define da qualche parte per i sizeof! E usarla qui al posto di 4!
    {
        uint32_t* valueLengthPointer32bit = (uint32_t*)socket->receiveMessage(sizeof(uint32_t));
        valueLength = *valueLengthPointer32bit;
        free(valueLengthPointer32bit);
    }
    break;
    case 8: //TODO mettere delle define da qualche parte per i sizeof! E usarla qui al posto di 8!
    {
        uint64_t* valueLengthPointer64bit = (uint64_t*)socket->receiveMessage(sizeof(uint64_t));
        valueLength = *valueLengthPointer64bit;
        free(valueLengthPointer64bit);
    }
    break;
    }

    void* value = NULL;
    if(valueLength == 0)
        {
        //TODO: throw exception??
        }
    else
        {
            value = socket->receiveMessage(valueLength);
        }
    return buildersHierarchy.delegateBuilding(receivedType, valueLength, value); //NB: la guild deve fare la free del value
}

void Service::receiveParameters()
{
    SerializableObjectList::size_type inputParametersSize = inputParameters.size();
    SerializableObjectList::size_type* incomingParametersSizePointer =
        ((SerializableObjectList::size_type*)socket->receiveMessage(sizeof(SerializableObjectList::size_type)));
    SerializableObjectList* incomingParameters = new SerializableObjectList;
    SerializableObjectList::size_type incomingParametersSize = *incomingParametersSizePointer;
    free(incomingParametersSizePointer);
    if(incomingParametersSize != inputParametersSize)
    {



    }
    for(unsigned int i = 0; i < inputParametersSize; i++)
    {
        //TODO controllo sul tipo ritornato dal server!
        incomingParameters->push_back(receiveParameter());
    }
    SerializableObjectList::iterator i = inputParameters.begin();
    SerializableObjectList::iterator j = incomingParameters->begin();
    while(i != inputParameters.end())
    {
        *(*i) = *(*j);
        i++;
        j++;
    }
    delete incomingParameters;
}

void Service::updateServiceID(SerializableObject* parameterToAdd, Direction parameterDirection)
{
    string directionString;
    switch(parameterDirection)
        {
            case IN:
                {
                    directionString = " IN: ";
                }
            break;
            case OUT:
                {
                    directionString = " OUT: ";
                }
            break;
            case INOUT:
                {
                    directionString = " INOUT: ";
                }
            break;
            case OUTIN:
                {
                    directionString = " OUTIN: ";
                }
            break;
            default:
                {
                    directionString = " <unknown direction>: ";
                }
            break;
        }
    directionString.append(parameterToAdd->getValueTypeStringRepresentation()).append(")");
    cout << "ServiceID prima della replace: " << serviceID << endl;
    serviceID.replace(serviceID.find_last_of(')'), 1, directionString);
    cout << "ServiceID corrente: " << serviceID << endl;
}
