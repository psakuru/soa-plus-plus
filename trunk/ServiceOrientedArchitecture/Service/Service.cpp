#include "Service.h"
#include "../../contaTab.h"
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
    tabs++;
    //cout << tab() << "BEGIN: Service.Service()" << endl;
    cout << "Cool!" << endl;
    defaultBuildersHierarchyInit();
    socket = NULL; //Il socket va inizializzato ai livelli sottostanti
    //cout << tab() << "END: Service.Service()" << endl;
    tabs--;
}

Service::Service(string serviceIDToSet) : serviceID(serviceIDToSet)
{
    //cout << "TID:" << boost::this_thread::get_id() << " Service("  << serviceIDToSet << ")" << endl << endl;
    tabs++;
    //cout << tab() << "BEGIN: Service.Service(string serviceIDToSet)" << endl;
    //cout << tab() << "Ho ricevuto il serviceID " << serviceIDToSet << ", lo setto" << endl;
    //cout << tab() << "Inizializzo la buildersHierarchy" << endl;
    serviceID.append("()");
    cout << "ServiceID corrente: " << serviceID << endl;
    cout << "Vingilioth:::: vengo richiamato io, maremma cane! serviceID: " << serviceID << " this:" << hex << (void*)this << endl;
    defaultBuildersHierarchyInit();
    //cout << tab() << "Setto il socket a null: chi mi eredita lo setterà a dovere" << endl;
    socket = NULL; //Il socket va inizializzato ai livelli sottostanti
    //cout << tab() << "END: Service.Service(string serviceIDToSet)" << endl;
    tabs--;
}

Service::~Service()
{
    tabs++;
    //cout << tab() << "BEGIN: Service.~Service()" << endl;
    delete socket;
    //cout << tab() << "END: Service.~Service()" << endl;
    tabs--;
}

void Service::defaultBuildersHierarchyInit()
{
    cout << "TID:" << boost::this_thread::get_id() << " Service::defaultBuildersHierarchyInit()" << endl << endl;
    tabs++;
    //cout << tab() << "BEGIN: Service.defaultBuildersHierarchyInit()" << endl;
    buildersHierarchy.addSerializableObjectBuilder(SERIALIZABLE_INTEGER, new TerminalSerializableObjectBuilder<Integer>());
    buildersHierarchy.addSerializableObjectBuilder(SERIALIZABLE_REAL, new TerminalSerializableObjectBuilder<Real>());
    buildersHierarchy.addSerializableObjectBuilder(SERIALIZABLE_STRING, new TerminalSerializableObjectBuilder<String>());
    buildersHierarchy.addSerializableObjectBuilder(SERIALIZABLE_RAW_BYTE_BUFFER, new TerminalSerializableObjectBuilder<RawByteBuffer>());
    buildersHierarchy.addSerializableObjectBuilder(SERIALIZABLE_SIGNAL, new SignalBuilder());
    buildersHierarchy[SERIALIZABLE_SIGNAL]->addSerializableObjectBuilder(SIGNAL_BAD_REQUEST, new TerminalSerializableObjectBuilder<BadRequest>());
    //cout << tab() << "END: Service.defaultBuildersHierarchyInit()" << endl;
    tabs--;
}

void Service::sendParameters()
{
    tabs++;
    //cout << tab() << "BEGIN: Service.Service(string serviceIDToSet)" << endl;
    //cout << tab() << "Prendo la dimensione della lista di input" << endl;
    SerializableObjectList::size_type listSize = outputParameters.size();
    socket->sendMessage(&listSize, sizeof(SerializableObjectList::size_type));
    //cout << "Dimensione lista inviata" << endl;
    SerializableObjectList::iterator i = outputParameters.begin();
    void* serializedObject = NULL;
    for(; i != outputParameters.end(); i++)
    {
        uint64_t serializedObjectLength = (*i)->serialize(&serializedObject);
        socket->sendMessage(serializedObject, serializedObjectLength);
        free(serializedObject);
        serializedObject = NULL;
    }
    //cout << tab() << "END: Service.Service(string serviceIDToSet)" << endl;
    tabs--;
}

SerializableObject* Service::receiveParameter()
{
    //TODO trovare un modo per fare la receive senza stare a fare la free del puntatore
    Type* receivedTypePointer = ((Type*)socket->receiveMessage(sizeof(Type)));
    Type receivedType = *receivedTypePointer;
    cout << "Tipo ricevuto: " << receivedType << endl;
    free(receivedTypePointer);
    int valueLengthLength = buildersHierarchy.getValueLengthLength(receivedType);
    //cout << "Lunghezza del campo length da ricevere: " << valueLengthLength << endl;
    /*
    uint64_t valueLength =
        (valueLengthLength == 0)? 0:
        (valueLengthLength == sizeof(uint8_t ))? *((uint8_t*)socket->receiveMessage(sizeof(uint8_t))) :
        (valueLengthLength == sizeof(uint16_t))? *((uint16_t*)socket->receiveMessage(sizeof(uint16_t))) :
        (valueLengthLength == sizeof(uint32_t))? *((uint32_t*)socket->receiveMessage(sizeof(uint32_t))) :
        (valueLengthLength == sizeof(uint64_t))? *((uint64_t*)socket->receiveMessage(sizeof(uint64_t))) : 0;
    */
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
    //cout << "Campo length: " << valueLength << endl;
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
    SerializableObjectList* incomingParameters = new SerializableObjectList;
    SerializableObjectList::size_type inputParametersSize = inputParameters.size();
    SerializableObjectList::size_type* incomingParametersSizePointer =
        ((SerializableObjectList::size_type*)socket->receiveMessage(sizeof(SerializableObjectList::size_type)));
    SerializableObjectList::size_type incomingParametersSize = *incomingParametersSizePointer;
    free(incomingParametersSizePointer);
    if(incomingParametersSize != inputParametersSize)
    {
        //cout << "Eccezione: dimensione della lista in arrivo non esatta!" << endl;
        //cout << "\t dovrebbe essere: " << (int)inputParametersSize << endl;
        //cout  << "\t e invece è: " << (int)incomingParametersSize << endl;
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
