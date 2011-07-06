#ifndef REGISTRABLEPOOLABLECALLABLESKELETONWRAPPER_H
#define REGISTRABLEPOOLABLECALLABLESKELETONWRAPPER_H

#include "../PoolableCallableSkeletonWrapper.h"
#include "../../../../../../ObjectInterfaces/RegistrableObject/RegistrableObject.h"

template <typename T>
class RegistrablePoolableCallableSkeletonWrapper : public RegistrableObject, public PoolableCallableSkeletonWrapper<T>
{
public:
    string getRegistrationInfo()
    {
        cout << "Fino al RegistrablePoolableCallableSkeletonWrapper ci arrivo" << endl;
        T dummyT;
        return dummyT.getRegistrationInfo();
    }
};

#endif // REGISTRABLEPOOLABLECALLABLESKELETONWRAPPER_H
