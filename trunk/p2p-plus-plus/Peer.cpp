#include "Peer.h"
#include "../SerializableObject/SerializationStrategies/StringSerializationStrategy/StringSerializationStrategy.h"

Peer::Peer() {}

Peer::Peer(string serviceIDToSet, string registryAddressToSet)
    : serviceID(serviceIDToSet), registryAddress(registryAddressToSet) {}

Peer::~Peer()
{
    vector<TcpIpActiveSocket*>::iterator i = sockets.front();
    for(; i!= sockets.back(); i++)
    {
        delete (*i);
    }
    vector<TcpIpActiveSocket*>::iterator j = inputParameters.front();
    for(; != inputParameters.back(); j++)
    {
        list<SerializableObject*>::iterator k = inputParameters[j].begin();
        for(; k != inputParameters[j].end(); k++)
        {
            delete (*k);
        }
    }
    vector<TcpIpActiveSocket*>::iterator l = outputParameters.front();
    for(; != outputParameters.back(); l++)
    {
        list<SerializableObject*>::iterator k = outputParameters[l].begin();
        for(; k != outputParameters[l].end(); k++)
        {
            delete (*k);
        }
    }
}

void Peer::bind() //Protocollo: mando il serviceID al register e mi aspetto una lista con gli indirizzi dei peer
{
    String requestedService(serviceID);
    inputParameters.push_back(*(new list<SerializableObject*>)); //TODO sarebbe da continuare... Ma il tempo stringe...
    inputParameters[0].push_back(&requestedService); //lista dei parametri di IN per il peer 0
    sockets.push_back(*(new TcpIpActiveSocket(registryAddress, 4000)));
    sendParameters(0);
    receiveResponseParameters(0);
    peerAddresses.resize(0);
    list<SerializableObject*>*::iterator i = outputParameters[0].begin();
    for(; i != outputParameters[0].end(); i++)
    {
        peerAddresses.push_back(*((string*)((*i)->getValue())));
    }
    sockets.resize(0);
    vector<string>::iterator j = peerAddresses.front();
    for(; j != peerAddresses.back(); j++)
    {
        sockets.push_back(*(new TcpIpActiveSocket((*j)/*prima parte: IP*/,/*seconda parte: porta*/)); //TODO FORSE SI RIESCE, FAI IL PARSING DELL' INDIRIZZO
    }
}
