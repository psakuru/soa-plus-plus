#include "TcpIpSocket.h"
#include "Exceptions/SocketException.h"
using namespace std;

TcpIpSocket::TcpIpSocket()
{
    socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if(socketDescriptor < 0)
    {
        throw SocketException();
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
