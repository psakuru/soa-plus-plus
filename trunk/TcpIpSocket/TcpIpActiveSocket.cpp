#include "TcpIpActiveSocket.h"
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#include <strings.h>
#include <iostream>
#include <errno.h>
#include <string.h>
using namespace std;

TcpIpActiveSocket::TcpIpActiveSocket()
{
    //ctor
}

TcpIpActiveSocket::TcpIpActiveSocket(string serverIPorURL, int port)
{
    hostent* server = gethostbyname(serverIPorURL.c_str());
    //TODO: eccezioni
    bzero((char *) &serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serverAddress.sin_addr.s_addr, server->h_length);
    serverAddress.sin_port = htons(port);
    connect(socketDescriptor, (sockaddr*)&serverAddress, sizeof(serverAddress));
    //TODO: eccezioni
}

TcpIpActiveSocket::TcpIpActiveSocket(int listeningSocketDescriptor) : TcpIpSocket(0)
{
    socklen_t addressLength = 0;
    socketDescriptor = accept(listeningSocketDescriptor, (sockaddr*)&serverAddress, &addressLength);
    strerror(errno);
    //TODO: eccezioni
}

TcpIpActiveSocket::~TcpIpActiveSocket()
{
    cout << "Socket attivo chiuso" << endl;
    close(socketDescriptor);
}


void TcpIpActiveSocket::sendMessage(void* buffer, uint64_t length)
{
    write(socketDescriptor, buffer, length);
}

void* TcpIpActiveSocket::receiveMessage(uint64_t length)
{
    void* bufferToReturn = malloc(length);
    read(socketDescriptor, bufferToReturn, length);
    return bufferToReturn;
}
