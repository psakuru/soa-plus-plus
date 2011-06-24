#include "TcpIpPassiveSocket.h"
#include <unistd.h>
#include <netdb.h>
#include <strings.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <iostream>
#include <stdexcept>
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

string TcpIpPassiveSocket::getAddress()
{
    string address;
    address.append(inet_ntoa(serverAddress.sin_addr)).append(":").append(boost::lexical_cast<string>(ntohs(serverAddress.sin_port)));
    return address;

}
