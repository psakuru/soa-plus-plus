#include "TcpIpSocket.h"
#include <string.h>
#include <errno.h>
#include <stdexcept>
using namespace std;

TcpIpSocket::TcpIpSocket()
{
    socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if(socketDescriptor < 0)
    {
        runtime_error socketException(strerror(errno));
        throw socketException;
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
