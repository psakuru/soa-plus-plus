#ifndef REGISTRABLESKELETON_H
#define REGISTRABLESKELETON_H

#include "../Skeleton.h"
#include "../../../../ObjectInterfaces/RegistrableObject/RegistrableObject.h"

class RegistrableSkeleton : public RegistrableObject, virtual public Skeleton
{
public:
    RegistrableSkeleton();
    RegistrableSkeleton(string serviceIDToSet);
    RegistrableSkeleton(string serviceIDToSet, TcpIpPassiveSocket* listeningSocketToShare);
    string getRegistrationInfo();
};

#endif // REGISTRABLESKELETON_H
