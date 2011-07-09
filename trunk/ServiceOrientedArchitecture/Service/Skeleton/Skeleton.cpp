#include "Skeleton.h"
#include <cstddef>
#include <iostream>
#include "../Exceptions/ParameterDirectionException.h"
using namespace std;

Skeleton::Skeleton() : listeningSocket(NULL), sharedListeningSocket(false) {} //TODO TRUE

Skeleton::Skeleton(string serviceIDToSet)
    : Service(serviceIDToSet), listeningSocket(NULL), sharedListeningSocket(false) {} //TODO TRUE

Skeleton::Skeleton(string serviceIDToSet, TcpIpPassiveSocket* listeningSocketToShare)
    : Service(serviceIDToSet), listeningSocket(listeningSocketToShare), sharedListeningSocket(true) {}

Skeleton::Skeleton(string serviceIDToSet, string IPAddress, int port, int backlog)
    : Service(serviceIDToSet)
{
	sharedListeningSocket = false;
	listeningSocket = NULL;
    listeningSocket = new TcpIpPassiveSocket(IPAddress, port, backlog);
}

Skeleton::~Skeleton()
{
    if(!sharedListeningSocket)
    {
        delete listeningSocket;
    }
    listeningSocket = NULL; //Così il distruttore di Service non distrugge il socket condiviso
}

void Skeleton::shareListeningSocket(TcpIpPassiveSocket* listeningSocketToShare)
{
	if(!sharedListeningSocket) //TODO attenzione cehe abbiamo aggiunto sta roba. cosimo non è sicuro che funzioni.
    {
        delete listeningSocket;
    }
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
    try
    {
        receiveParameters();
    }
    catch(const exception& caughtException)
    {
        cout << caughtException.what() << endl;
        return;
    }
    this->doService();
    sendParameters();
    outputParameters.clear(); // La lista di output contenteva i parametri inviati, quindi è possibile cancellarla.
							  // La lista di input invece continua a mantenere i tipi che il servente si aspetta.
}

void Skeleton::addParameter(SerializableObject* parameterToAdd, Direction parameterDirection)
{
    if(parameterDirection == OUT || parameterDirection == OUTIN)
    {
        throw ParameterDirectionException();
    }
    inputParameters.push_back(parameterToAdd);
    updateServiceID(parameterToAdd, parameterDirection);
}
