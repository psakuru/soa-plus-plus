#ifndef REGISTRABLESKELETONTHREADPOOL_H
#define REGISTRABLESKELETONTHREADPOOL_H

#include "../SkeletonThreadPool.h"
#include <iostream>
using namespace std;

template <typename T, int poolSize> class RegistrableSkeletonThreadPool
    : public RegistrableObject, public SkeletonThreadPool<T, poolSize>
{
public:
    RegistrableSkeletonThreadPool(string IPAddress, int listeningPort, int backlog)
        : SkeletonThreadPool<T, poolSize>(IPAddress, listeningPort, backlog)
    {
    }
    string getRegistrationInfo()
    {
        cout << "Fino a SkeletonThreadPool ci arrivo" << endl;
        if(!SkeletonThreadPool<T, poolSize>::threadReferences.empty())
        {
            cout << "Fino a SkeletonThreadPool ci arrivo" << endl;
            T dummyT;
            string registrationInfoToReturn = dummyT.getRegistrationInfo();
            registrationInfoToReturn.append(SkeletonThreadPool<T, poolSize>::sharedListeningSocket.getAddress());
            cout << "Ecco registrationInfoToReturn: " << registrationInfoToReturn << endl;
            return registrationInfoToReturn;
        }
        else
        {
            runtime_error emptyPool("The pool is empty, thus it cannot be registrated.");
            throw emptyPool;
        }
        return "<empty>";
    }
};

#endif // REGISTRABLESKELETONTHREADPOOL_H
