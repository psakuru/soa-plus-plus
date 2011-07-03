#ifndef SKELETON_H
#define SKELETON_H

#include "../Service.h"
#include "../../../TcpIpSocket/TcpIpPassiveSocket/TcpIpPassiveSocket.h"

class Skeleton : public Service
{
protected:
    TcpIpPassiveSocket* listeningSocket;
    /*<attenzione>*/
    bool sharedListeningSocket;
    /*</attenzione>*/
    void bind();
    void protocol();
    virtual void doService() = 0;
    void addParameter(SerializableObject* parameterToAdd, Direction parameterDirection);
public:
    Skeleton();
    Skeleton(string serviceIDToSet);
    /*<attenzione>*/
    Skeleton(string serviceIDToSet, TcpIpPassiveSocket* listeningSocketToShare);
    /*</attenzione>*/
    Skeleton(string serviceIDToSet, string IPAddress, int port, int backlog);
    virtual ~Skeleton();
    void shareListeningSocket(TcpIpPassiveSocket* listeningSocketToShare);
};

#endif // SKELETON_H
