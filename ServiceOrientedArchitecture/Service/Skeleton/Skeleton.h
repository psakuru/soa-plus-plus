#ifndef SKELETON_H
#define SKELETON_H

#include "../Service.h"
#include "../../../TcpIpSocket/TcpIpPassiveSocket.h"

class Skeleton : public Service
{
    private:
        TcpIpPassiveSocket* listeningSocket;
    protected:
        string serviceRegistryAddress;
        void bind();
        void protocol();
        virtual void doService() = 0;
    public:
        Skeleton();
        Skeleton(string serviceIDToSet, int port, int backlog);
        virtual ~Skeleton();
};

#endif // SKELETON_H
