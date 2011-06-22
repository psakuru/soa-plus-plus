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

Skeleton::Skeleton(string serviceIDToSet, int port, int backlog)
    : Service(serviceIDToSet)
{
    listeningSocket = new TcpIpPassiveSocket(port, backlog);
    sharedListeningSocket = false;
}

Skeleton::~Skeleton()
{
    if(!sharedListeningSocket) {delete listeningSocket;}
}

void Skeleton::shareListeningSocket(TcpIpPassiveSocket* listeningSocketToShare)
{
    listeningSocket = listeningSocketToShare;
    sharedListeningSocket = true;
}

void Skeleton::bind()
{
    socket = listeningSocket->acceptConnection();
    protocol();
}

void Skeleton::protocol()
{
    //TODO try{
    receiveParameters();
    //TODO
    //TODO catch(badParameters) rispondi BadRequest
    this->doService();
    sendParameters();
    outputParameters.clear();
}
