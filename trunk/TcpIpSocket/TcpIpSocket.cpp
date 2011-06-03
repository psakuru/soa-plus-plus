#include "TcpIpSocket.h"

TcpIpSocket::TcpIpSocket()
{
    socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
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
