#include "TcpIpPassiveSocket.h"
#include <unistd.h>
#include <netdb.h>
#include <strings.h>

TcpIpPassiveSocket::TcpIpPassiveSocket()
{
    //ctor
}

TcpIpPassiveSocket::TcpIpPassiveSocket(int listeningPort, int backlog)
{
    bzero((char *) &serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(listeningPort);
    bind(socketDescriptor, (sockaddr*) &serverAddress, sizeof(serverAddress));
    //TODO eccezioni
    listen(socketDescriptor,backlog);
}

TcpIpActiveSocket* TcpIpPassiveSocket::acceptConnection()
    {
    TcpIpActiveSocket* socketToReturn = new TcpIpActiveSocket(socketDescriptor);
    return socketToReturn;
    }

TcpIpPassiveSocket::~TcpIpPassiveSocket()
{
    close(socketDescriptor);
}
