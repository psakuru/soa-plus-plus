#ifndef TCPIPACTIVESOCKET_H
#define TCPIPACTIVESOCKET_H

#include "../TcpIpSocket.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
using namespace std;

class TcpIpActiveSocket : public TcpIpSocket
{
protected:
    sockaddr_in serverAddress;
public:
    TcpIpActiveSocket();
    TcpIpActiveSocket(string serverIPorURL, int port);
    TcpIpActiveSocket(int listeningSocketDescriptor);
    ~TcpIpActiveSocket();
    string getAddress();
    void sendMessage(void* buffer, uint64_t length);
    void* receiveMessage(uint64_t length);
};

#endif // TCPIPACTIVESOCKET_H
