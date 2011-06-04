#include "TcpIpSocket.h"
#include <string.h>
#include <errno.h>

TcpIpSocket::TcpIpSocket()
{
    socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if(socketDescriptor < 0)
        {
        strerror(errno);
        }
    //TODO gestione eccezioni
}

TcpIpSocket::TcpIpSocket(int NOP)
{
    socketDescriptor = 0;
    //TODO gestione eccezioni
}

TcpIpSocket::~TcpIpSocket()
    {
    }
