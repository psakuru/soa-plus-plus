#ifndef PEER_H
#define PEER_H

#include <string>
#include <vector>
#include <list>
#include "../TcpIpSocket/TcpIpActiveSocket.h"
#include "../SerializableObject/SerializableObject.h"
using namespace std;

class Peer
{
    private:
        string serviceID;
        string registryAddress;
    protected:
        vector<string> peerAddresses;
        vector<TcpIpActiveSocket*> sockets;
        vector< list<SerializableObject*> > inputParameters;
        vector< list<SerializableObject*> > outputParameters;
        void sendParameters(int peerIndex);
        void receiveResponseParameters(int peerIndex);
        void bind();
        virtual void protocol() = 0;
    public:
        Peer();
        Peer(string serviceIDToSet, string registryAddressToSet);
        ~Peer();
};

#endif // PEER_H
