#ifndef POOLABLECYCLICCALLABLESKELETON_H
#define POOLABLECYCLICCALLABLESKELETON_H

#include "../Skeleton.h"
#include "../../CallableService/CallableService.h"
#include "../../../../TcpIpSocket/TcpIpPassiveSocket.h"
#include <boost/thread/mutex.hpp>

class PoolableCyclicCallableSkeleton : public CallableService<Skeleton>
{
    private:
        boost::mutex* sharedMutex;
    public:
        PoolableCyclicCallableSkeleton(string serviceIDToSet); // Il ParticularPoolableCyclicCallableSkeleton conosce nel suo
        //costruttore di default il serviceIDToSet;
        virtual ~PoolableCyclicCallableSkeleton();
        void shareMutex(boost::mutex* mutexToShare);
        virtual void operator()();
};

#endif // POOLABLECYCLICCALLABLESKELETON_H
