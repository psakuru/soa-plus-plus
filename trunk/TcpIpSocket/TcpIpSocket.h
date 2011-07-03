#ifndef TCPIPSOCKET_H
#define TCPIPSOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
using namespace std;

class TcpIpSocket
{
protected:
    int socketDescriptor;
public:
    TcpIpSocket();
    TcpIpSocket(int NOP);
    virtual ~TcpIpSocket();
    virtual string getAddress() = 0;
};

#endif // TCPIPSOCKET_H
