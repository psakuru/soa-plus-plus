#ifndef POOLABLECYCLICCALLABLESKELETON_H
#define POOLABLECYCLICCALLABLESKELETON_H

#include "../Skeleton.h"
#include "../RegistrableSkeleton/RegistrableSkeleton.h"
#include "../../CallableService/CallableService.h"
#include "../../../../TcpIpSocket/TcpIpPassiveSocket.h"
#include <boost/thread/mutex.hpp>

class RegistrablePoolableCyclicCallableSkeleton : public RegistrableSkeleton, public CallableService<Skeleton>
{
    private:
        boost::mutex* sharedMutex;
    public:
        RegistrablePoolableCyclicCallableSkeleton(string serviceIDToSet); // Il ParticularPoolableCyclicCallableSkeleton conosce nel suo
        //costruttore di default il serviceIDToSet;
        virtual ~RegistrablePoolableCyclicCallableSkeleton();
        void shareMutex(boost::mutex* mutexToShare);
        virtual void operator()();
};

#endif // POOLABLECYCLICCALLABLESKELETON_H
