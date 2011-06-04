#include "TcpIpPassiveSocket.h"
#include <unistd.h>
#include <netdb.h>
#include <strings.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <iostream>
using namespace std;

TcpIpPassiveSocket::TcpIpPassiveSocket()
{
    //ctor
}

TcpIpPassiveSocket::TcpIpPassiveSocket(int listeningPort, int backlog)
{
    bzero((char *) &serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");//INADDR_ANY;
    serverAddress.sin_port = htons(listeningPort);
    bind(socketDescriptor, (sockaddr*) &serverAddress, sizeof(serverAddress));
    strerror(errno);
    //TODO eccezioni
    listen(socketDescriptor,backlog);
    strerror(errno);
}

TcpIpActiveSocket* TcpIpPassiveSocket::acceptConnection()
    {
    TcpIpActiveSocket* socketToReturn = new TcpIpActiveSocket(socketDescriptor);
    return socketToReturn;
    }

TcpIpPassiveSocket::~TcpIpPassiveSocket()
{
    cout << "Socket passivo chiuso" << endl;
    close(socketDescriptor);
}
