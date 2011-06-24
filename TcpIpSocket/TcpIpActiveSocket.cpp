#include "TcpIpActiveSocket.h"
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#include <strings.h>
#include <iostream>
#include <errno.h>
#include <string.h>
#include <stdexcept>
#include <boost/lexical_cast.hpp>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;

TcpIpActiveSocket::TcpIpActiveSocket()
{
    //ctor
}

TcpIpActiveSocket::TcpIpActiveSocket(string serverIPorURL, int port)
{
    hostent* server = gethostbyname(serverIPorURL.c_str());
    if(server == NULL)
    {
        runtime_error gethostbynameException("Cannot retrieve host from the specified URL/IP address.");
        throw gethostbynameException;
    }
    //TODO: eccezioni
    bzero((char *) &serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serverAddress.sin_addr.s_addr, server->h_length);
    serverAddress.sin_port = htons(port);
    int error = connect(socketDescriptor, (sockaddr*)&serverAddress, sizeof(serverAddress));
    if(error < 0)
    {
        runtime_error connectException(strerror(errno));
        throw connectException;
    }
    //TODO: eccezioni
}

TcpIpActiveSocket::TcpIpActiveSocket(int listeningSocketDescriptor) : TcpIpSocket(0)
{
    socklen_t addressLength = 0;
    socketDescriptor = accept(listeningSocketDescriptor, (sockaddr*)&serverAddress, &addressLength);
    if(socketDescriptor < 0)
    {
        runtime_error acceptException(strerror(errno));
        throw acceptException;
    }
    //TODO: eccezioni
}

TcpIpActiveSocket::~TcpIpActiveSocket()
{
    //cout << "Socket attivo chiuso" << endl;
    int error = close(socketDescriptor);
    if(error < 0)
    {
        runtime_error closeException(strerror(errno));
        throw closeException;
    }
}

void TcpIpActiveSocket::sendMessage(void* buffer, uint64_t length)
{
    int error = send(socketDescriptor, buffer, length, 0);
    if(error < 0)
    {
        runtime_error writeException(strerror(errno));
        throw writeException;
    }
    cout << "SOCKET>> " << length << " bytes sent" << endl;
}

void* TcpIpActiveSocket::receiveMessage(uint64_t length)
{
    void* bufferToReturn = malloc(length);
    uint64_t readBytes = recv(socketDescriptor, bufferToReturn, length, MSG_WAITALL);
    /*while(readBytes < length) //TODO bisogna trovare il modo di lanciare la timeout exception, ad esempio consentendo 
    un num max di cicli
    {
        readBytes += read(socketDescriptor, (void*)(((uint8_t*)bufferToReturn)+readBytes), length - readBytes);*/
        if(readBytes < 0)
        {
            runtime_error readException(strerror(errno));
            throw readException;
        }
    //}
    cout << "SOCKET<< " << readBytes << " bytes received" << endl;
    return bufferToReturn;
}

string TcpIpActiveSocket::getAddress()
{
    string address;
    address.append(inet_ntoa(serverAddress.sin_addr)).append(":").append(boost::lexical_cast<string>(ntohs(serverAddress.sin_port)));
    return address;
}
