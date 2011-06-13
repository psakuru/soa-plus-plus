#ifndef TCPIPSOCKET_H
#define TCPIPSOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

class TcpIpSocket
{
protected:
        int socketDescriptor;
public:
        TcpIpSocket();
        TcpIpSocket(int NOP);
        virtual ~TcpIpSocket();
};

#endif // TCPIPSOCKET_H
