#include "Skeleton.h"

Skeleton::Skeleton()
{
}

Skeleton::Skeleton(string serviceIDToSet, int port, int backlog)
    : Service(serviceIDToSet)
{
    listeningSocket = new TcpIpPassiveSocket(port, backlog);
}

Skeleton::~Skeleton()
{
    delete listeningSocket;
}

void Skeleton::bind()
{
    socket = listeningSocket->acceptConnection();
    protocol();
}

void Skeleton::protocol()
{
    receiveParameters();
    this->doService();
    sendParameters();
    outputParameters.clear();
}
