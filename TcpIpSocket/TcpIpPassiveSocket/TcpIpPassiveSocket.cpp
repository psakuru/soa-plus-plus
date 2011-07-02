#include "TcpIpPassiveSocket.h"
#include <unistd.h>
#include <netdb.h>
#include <strings.h>
#include <arpa/inet.h>
#include <iostream>
#include "../Exceptions/SocketException.h"
#include <boost/lexical_cast.hpp>
using namespace std;

TcpIpPassiveSocket::TcpIpPassiveSocket()
{
    //ctor
}

TcpIpPassiveSocket::TcpIpPassiveSocket(string IPAddress, int listeningPort, int backlog)
{
    bzero((char *) &serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(IPAddress.c_str());
    serverAddress.sin_port = htons(listeningPort);
    int error = bind(socketDescriptor, (sockaddr*) &serverAddress, sizeof(serverAddress));
    if(error < 0)
    {
        throw SocketException();
    }
    //TODO eccezioni
    error = listen(socketDescriptor,backlog);
    if(error < 0)
    {
        throw SocketException();
    }
}

TcpIpActiveSocket* TcpIpPassiveSocket::acceptConnection()
{
    TcpIpActiveSocket* socketToReturn = new TcpIpActiveSocket(socketDescriptor);
    return socketToReturn;
}

TcpIpPassiveSocket::~TcpIpPassiveSocket()
{

    int error = close(socketDescriptor);
    if(error < 0)
    {
        throw SocketException();
    }
}

string TcpIpPassiveSocket::getAddress()
{
    string address;
    address.append(inet_ntoa(serverAddress.sin_addr));
    address.append(":").append(boost::lexical_cast<string>(ntohs(serverAddress.sin_port)));
    return address;
}
