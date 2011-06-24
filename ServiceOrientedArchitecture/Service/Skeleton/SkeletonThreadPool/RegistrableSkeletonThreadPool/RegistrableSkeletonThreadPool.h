#ifndef REGISTRABLESKELETONTHREADPOOL_H
#define REGISTRABLESKELETONTHREADPOOL_H

#include "../SkeletonThreadPool.h"

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
        if(!SkeletonThreadPool<T, poolSize>::threadReferences.empty())
        {
            T dummyT;
            return dummyT.getRegistrationInfo();
        }
        else
        {
            runtime_error emptyPool("The pool is empty, thus it cannot be registrated.");
            throw emptyPool;
        }
    }
};

#endif // REGISTRABLESKELETONTHREADPOOL_H
