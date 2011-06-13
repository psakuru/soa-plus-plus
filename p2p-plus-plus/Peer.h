#ifndef PEER_H
#define PEER_H

#include <string>
#include <vector>
#include <boost/ptr_container/ptr_list.hpp>
#include "../TcpIpSocket/TcpIpActiveSocket.h"
#include "../SerializableObject/SerializableObject.h"
using namespace std;

typedef boost::ptr_list<SerializableObject> serializableObjectList;

class Peer
{
    private:
        string serviceID;
        string registryAddress;
    protected:
        vector<string> peerAddress;
        vector<TcpIpActiveSocket*> socket;
        vector<serializableObjectList> inputParameters;
        vector<serializableObjectList> outputParameters;
        void sendParameters(int peerIndex);
        void receiveParameter(int peerIndex);
        void receiveParameters(int peerIndex);
        void bind();
        virtual void protocol() = 0;
    public:
        Peer();
        Peer(string serviceIDToSet, string registryAddressToSet);
        ~Peer();
};

#endif // PEER_H
