#ifndef SKELETON_H
#define SKELETON_H

#include "../Service.h"
#include "../../../TcpIpSocket/TcpIpPassiveSocket.h"

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

    public:
        Skeleton();
        Skeleton(string serviceIDToSet);
        /*<attenzione>*/
        Skeleton(string serviceIDToSet, TcpIpPassiveSocket* listeningSocketToShare);
        /*</attenzione>*/
        Skeleton(string serviceIDToSet, int port, int backlog);
        virtual ~Skeleton();
        void shareListeningSocket(TcpIpPassiveSocket* listeningSocketToShare);
};

#endif // SKELETON_H
