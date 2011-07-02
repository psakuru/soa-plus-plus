#include "RegistrableSkeleton.h"
#include <iostream>
using namespace std;

RegistrableSkeleton::RegistrableSkeleton() {}

RegistrableSkeleton::RegistrableSkeleton(string serviceIDToSet)
    : Skeleton(serviceIDToSet) {}

RegistrableSkeleton::RegistrableSkeleton
(string serviceIDToSet, TcpIpPassiveSocket* listeningSocketToShare)
    : Skeleton(serviceIDToSet, listeningSocketToShare) {}

string RegistrableSkeleton::getRegistrationInfo()
{
    string registrationInfoToReturn = serviceID;
    registrationInfoToReturn.append("@");
    //registrationInfoToReturn.append(listeningSocket->getAddress());

    //return serviceID@IP:port*/
    return registrationInfoToReturn;
}
