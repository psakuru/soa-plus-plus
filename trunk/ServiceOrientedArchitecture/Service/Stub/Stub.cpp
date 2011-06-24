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
    //cout << "  BEGIN: Stub.Stub(string serviceIDToSet, string serviceRegistryAddressToSet)" << endl;
    //cout << "  Passati i parametri ricevuti al costruttore di Service" << endl;
    cout << "ServiceID settato su: " << serviceID << endl;
    serviceRegistryAddress = serviceRegistryAddressToSet;
    //cout << "  Settato il serviceRegistry" << endl;
    bind();
    //cout << "  END: Stub.Stub(string serviceIDToSet, string serviceRegistryAddressToSet)" << endl;
}

Stub::~Stub()
    {

    }

string Stub::getServiceRegistryAddress()
{
    return serviceRegistryAddress;
}

void Stub::setServiceRegistryAddress(string serviceRegistryAddressToSet)
{
    serviceRegistryAddress = serviceRegistryAddressToSet;
}

void Stub::rebind()
{
    //cout << "REBind dello stub!" << endl;
    bind();
}

void Stub::bind()
{
    //cout << "  BEGIN: Stub.bind()" << endl;
    //cout << "  BEGIN: Stub.bind()" << endl;
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
    /*SerializableObjectList::iterator i = inputParameters.begin();
    for(; i != inputParameters.end(); i++)
        {
        outputParameters.push_back(&(*i));
        }*/
    int outputParametersSize = (int)outputParameters.size();
    outputParameters.splice(outputParameters.end(), inputParameters);
    sendParameters();
    SerializableObjectList::iterator i = outputParameters.begin();
    advance(i, outputParametersSize);
    SerializableObjectList::iterator j = outputParameters.end();
    inputParameters.splice(inputParameters.begin(), outputParameters, i, j);
    receiveParameters();
}

void Stub::addParameter(SerializableObject* parameterToAdd, Direction parameterDirection)
{
    if(parameterDirection == IN || parameterDirection == INOUT)
    {
        runtime_error invalidParameterDirection("Invalid parameter direction.");
        throw invalidParameterDirection;
    }
    switch(parameterDirection)
    {
        case OUT:
        {
        outputParameters.push_back(parameterToAdd);
        }
        break;
        case OUTIN:
        {
        inputParameters.push_back(parameterToAdd);
        }
        break;
        default:
        break; //TODO eccezione?
    }
    parameterDirection = (parameterDirection == OUT)? IN : (parameterDirection == OUTIN)? INOUT : IN;
    updateServiceID(parameterToAdd, parameterDirection); //TODO Continua a mettere roba per aggiornare la firma nello StreamStub e nella roba di Skeleton
}
