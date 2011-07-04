#include "TcpIpActiveSocket.h"
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#include <strings.h>
#include <iostream>
#include "../Exceptions/UnknownHostException.h"
#include "../Exceptions/SocketException.h"
#include <boost/lexical_cast.hpp>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;

TcpIpActiveSocket::TcpIpActiveSocket(string serverIPorURL, int port)
{
    hostent* server = gethostbyname(serverIPorURL.c_str());
    if(server == NULL)
    {
        throw UnknownHostException();
    }
    bzero((char *) &serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serverAddress.sin_addr.s_addr, server->h_length);
    serverAddress.sin_port = htons(port);
    int error = connect(socketDescriptor, (sockaddr*)&serverAddress, sizeof(serverAddress));
    if(error < 0)
    {
        throw SocketException();
    }
}

TcpIpActiveSocket::TcpIpActiveSocket(int listeningSocketDescriptor) : TcpIpSocket(0)
{
    socklen_t addressLength = 0;
    socketDescriptor = accept(listeningSocketDescriptor, (sockaddr*)&serverAddress, &addressLength);
    if(socketDescriptor < 0)
    {
        throw SocketException();
    }
}

void TcpIpActiveSocket::sendMessage(void* buffer, uint64_t length)
{
    int error = send(socketDescriptor, buffer, length, 0);
    if(error < 0)
    {
        throw SocketException();
    }
    cout << "SOCKET>> " << dec << length << " bytes sent" << endl;
}

void* TcpIpActiveSocket::receiveMessage(uint64_t length)
{
    void* bufferToReturn = malloc(length);
    uint64_t readBytes = recv(socketDescriptor, bufferToReturn, length, MSG_WAITALL);
    if(readBytes < length) // Include sia le ricezioni incomplete che gli stati erronei ( < 0)
    {
        free(bufferToReturn);
        bufferToReturn = NULL;
        throw SocketException();
    }
    cout << "SOCKET<< " << dec << readBytes << " bytes received" << endl;
    return bufferToReturn;
}

string TcpIpActiveSocket::getAddress()
{
    string address;
    address.append(inet_ntoa(serverAddress.sin_addr)).append(":").append(boost::lexical_cast<string>(ntohs(serverAddress.sin_port)));
    return address;
}
