#include "TcpIpPassiveSocket.h"
#include <unistd.h>
#include <netdb.h>
#include <strings.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <iostream>
#include <stdexcept>
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
    int error = bind(socketDescriptor, (sockaddr*) &serverAddress, sizeof(serverAddress));
    if(error < 0)
    {
        runtime_error bindException(strerror(errno));
        throw bindException;
    }
    //TODO eccezioni
    error = listen(socketDescriptor,backlog);
    if(error < 0)
    {
        runtime_error listenException(strerror(errno));
        throw listenException;
    }
}

TcpIpActiveSocket* TcpIpPassiveSocket::acceptConnection()
    {
    TcpIpActiveSocket* socketToReturn = new TcpIpActiveSocket(socketDescriptor);
    return socketToReturn;
    }

TcpIpPassiveSocket::~TcpIpPassiveSocket()
{
    //cout << "Socket passivo chiuso" << endl;
    int error = close(socketDescriptor);
    if(error < 0)
    {
        runtime_error closeException(strerror(errno));
        throw closeException;
    }
}
