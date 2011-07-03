#include "Skeleton.h"
#include <boost/thread/thread.hpp>
#include <iostream>
using namespace std;

Skeleton::Skeleton() : listeningSocket(NULL), sharedListeningSocket(false) {}

Skeleton::Skeleton(string serviceIDToSet)
    : Service(serviceIDToSet), listeningSocket(NULL), sharedListeningSocket(false)
{
    cout << "TID:" << boost::this_thread::get_id() << " Skeleton("  << serviceIDToSet << ")" << endl << endl;
}

Skeleton::Skeleton(string serviceIDToSet, TcpIpPassiveSocket* listeningSocketToShare)
    : Service(serviceIDToSet), listeningSocket(listeningSocketToShare), sharedListeningSocket(true)
{}

Skeleton::Skeleton(string serviceIDToSet, string IPAddress, int port, int backlog)
    : Service(serviceIDToSet)
{
    listeningSocket = new TcpIpPassiveSocket(IPAddress, port, backlog);
    sharedListeningSocket = false;
}

Skeleton::~Skeleton()
{
    if(!sharedListeningSocket)
    {
        delete listeningSocket;
    }
}

void Skeleton::shareListeningSocket(TcpIpPassiveSocket* listeningSocketToShare)
{
    listeningSocket = listeningSocketToShare;
    sharedListeningSocket = true;
    cout << "ListeningSocket condiviso: " << (void*)listeningSocket << endl;
}

void Skeleton::bind()
{
    socket = listeningSocket->acceptConnection();
    protocol();
}

void Skeleton::protocol()
{
    try
    {
        receiveParameters();
    }
    catch(const exception& caughtException) // Il gestibile è già stato gestito
    {
        cout << caughtException.what() << endl;
        return;
    }
    this->doService();
    sendParameters();
    outputParameters.clear();
}

void Skeleton::addParameter(SerializableObject* parameterToAdd, Direction parameterDirection)
{
    if(parameterDirection == OUT || parameterDirection == OUTIN)
    {
        runtime_error invalidParameterDirection("Invalid parameter direction.");
        throw invalidParameterDirection;
    }
    inputParameters.push_back(parameterToAdd);
    updateServiceID(parameterToAdd, parameterDirection);
}
