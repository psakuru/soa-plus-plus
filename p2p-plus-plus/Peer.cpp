#include "Peer.h"
#include "../SerializableObject/SerializationStrategies/StringSerializationStrategy/StringSerializationStrategy.h"
#include "../SerializableObject/SerializationStrategies/IntegerSerializationStrategy/IntegerSerializationStrategy.h"

#define MAX_ACCEPTED_PEERS 10


//TODO È pieno di memory leak, praticamente dappertutto, in tutte le manipolazioni di vector e list!!!!!

Peer::Peer() {}

Peer::Peer(string serviceIDToSet, string registryAddressToSet)
    : serviceID(serviceIDToSet), registryAddress(registryAddressToSet)
{
    bind();
}

Peer::~Peer()
{
    vector<TcpIpActiveSocket*>::iterator i = socket.front();
    for(; i!= socket.back(); i++)
    {
        delete (*i);
    }
    //Le liste di puntatori a SerializableObject, essendo boost::ptr_list, fanno da sole la delete
}

void Peer::bind()
{
    String requestedService(serviceID); //Crea un SerializableObject String da inviare al register
    Integer maxAcceptedPeers(MAX_ACCEPTED_PEERS); //Da rendere configurabile!
    inputParameters.clear();
    outputParameters.clear();
    serializableObjectList requestToSendToRegister;
    inputParameters.push_back(requestToRegister);
    inputParameters[0].push_back(&requestedService); //lista dei parametri di IN per il peer 0
    TcpIpActiveSocket socketToSendRequest(registryAddress, 4000);
    socket.push_back(&socketToSendRequest);
    for(int i = 0; i < MAX_ACCEPTED_PEERS; i++)
    {
        String stringToPushBack;
        outputParameters[0].push_back(stringToPushBack);
    }
    sendParameters(0);
    receiveParameters(0);
    peerAddress.clear();
    list<SerializableObject*>*::iterator i = outputParameters[0].begin();
    for(; i != outputParameters[0].end(); i++)
    {
        string* addressToRegister = (string*)((*i)->getValue());
        peerAddress.push_back(addressToRegister);
        delete addressToRegister;
    }
    sockets.clear();
    vector<string>::iterator j = peerAddress.front();
    for(; j != peerAddress.back(); j++)
    {
        string ipAddress = (*j).substr(0, (*j).find_first_of(':'));
        string portString = (*j).substr((*j).find_first_of(':')+1);
        int port = atoi(portString.c_str());
        TcpIpActiveSocket socketToRegister(ipAddress, port);
        socket.push_back(*(new TcpIpActiveSocket(ipAddress, port));
    }
}

void Peer::sendParameters(int peerIndex)
{
    list<SerializableObject*>::size_type listSize = inputParameters[peerIndex].size();
    socket[peerIndex]->sendMessage(&listSize, sizeof(list<SerializableObject*>::size_type));
    list<SerializableObject*>::iterator i = inputParameters[peerIndex].begin();
    void* serializedObject = NULL;
    for(; i != inputParameters[peerIndex].end(); i++)
    {
        uint64_t serializedObjectLength = (*i)->serialize(&serializedObject);
        socket->sendMessage(serializedObject, serializedObjectLength);
        free(serializedObject);
        serializedObject = NULL;
    }
}

void Peer::receiveParameter(int peerIndex)
{
    //TODO trovare un modo per fare la receive senza stare a fare la free del puntatore
    Type* receivedTypePointer = ((Type*)socket[peerIndex]->receiveMessage(sizeof(Type)));
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

void Peer::receiveParameters(int peerIndex)
{
    list<SerializableObject*>::size_type receivedSize = socket[peerIndex]->receiveMessage(sizeof(list<SerializableObject*>::size_type));
    if(receivedSize != outputParameters[peerIndex].size())
    {
        //Throw exception!
    }
    list<SerializableObject*>* incomingParameters = new list<SerializableObject*>;
    list<SerializableObject*>::size_type outputListSize = outputParameters[peerIndex].size();
    for(int i = 0; i < outputListSize; i++)
    {
        //TODO controllo sul tipo ritornato dal server!
        incomingParameters->push_back(receiveParameter(peerIndex));
    }
    list<SerializableObject*>::iterator i = incomingParameters->begin();
    list<SerializableObject*>::iterator j = outputParameters[peerIndex].begin();
    while(i != incoming->end())
    {
        *(*j) = *(*i);
        i++;
        j++;
    }
}
