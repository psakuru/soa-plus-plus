#include "../../../SerializableObjects/DeserializationStrategies/TerminalSerializableObjectBuilder.h"
#include "../../../SerializableObjects/SerializationStrategies/IntegerSerializationStrategy/IntegerSerializationStrategy.h"
#include "../../../SerializableObjects/SerializationStrategies/RealSerializationStrategy/RealSerializationStrategy.h"
#include "../../../SerializableObjects/SerializationStrategies/StringSerializationStrategy/StringSerializationStrategy.h"
#include "../../../SerializableObjects/SerializationStrategies/RawByteBufferSerializationStrategy/RawByteBufferSerializationStrategy.h"
#include "../../../SerializableObjects/DeserializationStrategies/SignalBuilder.h"
#include "../../../SerializableObjects/SerializationStrategies/SignalSerializationStrategy/ParticularSignals/BadRequestSerializationStrategy/BadRequestSerializationStrategy.h"
#include "../../../TcpIpSocket/Exceptions/SocketException.h"
#include "Stub.h"

Stub::Stub() {}

Stub::Stub(string serviceIDToSet, string serviceRegistryAddressToSet)
    : Service(serviceIDToSet)
{
    //cout << "  BEGIN: Stub.Stub(string serviceIDToSet, string serviceRegistryAddressToSet)" << endl;
    //cout << "  Passati i parametri ricevuti al costruttore di Service" << endl;
    cout << "ServiceID settato su: " << serviceID << endl;
    serviceRegistryAddress = serviceRegistryAddressToSet;
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
    this->bind();
}

void Stub::bind()
{
    cout << "eseguita la giusta bind" << endl;
    SerializableObjectList outputParametersBackup(outputParameters);
    SerializableObjectList inputParametersBackup(inputParameters);
    // Non è una deep copy, vengono copiati i puntatori!
    int iterationsToEmptyList = (int)outputParameters.size();
    for(int i = 0; i < iterationsToEmptyList; i++)
    {
        outputParameters.pop_front(); //pop di un puntatore, non viene eliminato l' oggetto puntato!
    }
    iterationsToEmptyList = (int)inputParameters.size();
    for(int i = 0; i < iterationsToEmptyList; i++)
    {
        inputParameters.pop_front(); //pop di un puntatore, non viene eliminato l' oggetto puntato!
    }
    //Liste vuote: vanno riempite con la richiesta di bind al registro
    outputParameters.push_back(new String(new string("search"), false));
    outputParameters.push_back(new String(new string(serviceID),false));
    inputParameters.push_back(new String); //Per ricevere il service provider!
    staticallyBind(serviceRegistryAddress);
    protocol();
    delete socket;
    staticallyBind(*((string*)((inputParameters.front())->getValue())));
    inputParameters.clear();
    outputParameters.clear();
    inputParameters = inputParametersBackup; //copia dei puntatori
    outputParameters = outputParametersBackup; //copia dei puntatori
    cout << "dopo il protocollo di bind, ripristino le liste: inputParameters.size(): " << (int)inputParameters.size() << endl;
    cout << "dopo il protocollo di bind, ripristino le liste: outputParameters.size(): " << (int)outputParameters.size() << endl;
    iterationsToEmptyList = (int)inputParametersBackup.size();
    for(int i = 0; i < iterationsToEmptyList; i++)
    {
        inputParametersBackup.pop_front(); //pop di un puntatore, non viene eliminato l' oggetto puntato!
    }
    iterationsToEmptyList = (int)outputParametersBackup.size();
    for(int i = 0; i < iterationsToEmptyList; i++)
    {
        outputParametersBackup.pop_front(); //pop di un puntatore, non viene eliminato l' oggetto puntato!
    }
}

void Stub::staticallyBind(string serviceProviderAddressToSet)
{
    cout << "staticallyBind(" << serviceProviderAddressToSet << ")" << endl;
    serviceProviderAddress = serviceProviderAddressToSet;
    //TODO metodino (?) per il parsing degli indirizzi
    string ipAddress = serviceProviderAddress.substr(0, serviceProviderAddress.find_first_of(':'));
    string portString = serviceProviderAddress.substr(serviceProviderAddress.find_first_of(':')+1);
    int port = atoi(portString.c_str());
    //TODO check: e se il socket era stato inizializzato?
    try
    {
        socket = new TcpIpActiveSocket(ipAddress, port);
    }
    catch(const SocketException& socketException) //Eccezione in un costruttore:
    {
        socket = NULL;// mi accerto di poter fare la delete del socket nel processo di stack-unwinding
        //(non ho memory leaks non avendo allocazione dinamica)
        throw socketException;
    }
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


    /*SerializableObjectList::iterator k = outputParameters.begin();
    for(; k != outputParameters.end(); k++)
    {
        cout << "Modification:" << *((string*)((*k)->getValue())) << endl;
    }*/


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
        //runtime_error invalidParameterDirection("Invalid parameter direction.");
        //throw invalidParameterDirection;
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
