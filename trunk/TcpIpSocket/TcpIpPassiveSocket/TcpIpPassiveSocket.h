#ifndef TCPIPPASSIVESOCKET_H
#define TCPIPPASSIVESOCKET_H

#include "../TcpIpActiveSocket/TcpIpActiveSocket.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

class TcpIpPassiveSocket : public TcpIpSocket
{
protected:
        sockaddr_in serverAddress;
public:
        TcpIpPassiveSocket();
        TcpIpPassiveSocket(string IPAddress, int listeningPort, int backlog);
        ~TcpIpPassiveSocket();
        TcpIpActiveSocket* acceptConnection();
        string getAddress();
};

#endif // TCPIPPASSIVESOCKET_H
