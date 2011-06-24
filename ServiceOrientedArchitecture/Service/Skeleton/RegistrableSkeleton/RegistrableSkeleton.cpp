#include "RegistrableSkeleton.h"

RegistrableSkeleton::RegistrableSkeleton() {}

RegistrableSkeleton::RegistrableSkeleton(string serviceIDToSet)
    : Skeleton(serviceIDToSet) {}

RegistrableSkeleton::RegistrableSkeleton
(string serviceIDToSet, TcpIpPassiveSocket* listeningSocketToShare)
    : Skeleton(serviceIDToSet, listeningSocketToShare) {}

string RegistrableSkeleton::getRegistrationInfo()
{
    string registrationInfoToReturn;
    //return serviceID@IP:port
    return
        registrationInfoToReturn.append("@").append(listeningSocket->getAddress());
}
