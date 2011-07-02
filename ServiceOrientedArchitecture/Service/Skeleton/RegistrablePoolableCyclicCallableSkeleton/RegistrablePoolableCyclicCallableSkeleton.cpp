#include "RegistrablePoolableCyclicCallableSkeleton.h"
#include <boost/thread/thread.hpp>
#include <boost/pool/detail/guard.hpp>
#include "../../../../TcpIpSocket/Exceptions/SocketException.h"
#include <iostream>
using namespace std;

RegistrablePoolableCyclicCallableSkeleton::RegistrablePoolableCyclicCallableSkeleton(string serviceIDToSet)
    : Skeleton(serviceIDToSet), RegistrableSkeleton(serviceIDToSet), CallableService<Skeleton>(serviceIDToSet)
{
    cout << "TID:" << boost::this_thread::get_id() << " RegistrablePoolableCyclicCallableSkeleton(" << serviceIDToSet << ")" << endl << endl;
}

RegistrablePoolableCyclicCallableSkeleton::~RegistrablePoolableCyclicCallableSkeleton()
{
}

void RegistrablePoolableCyclicCallableSkeleton::shareMutex(boost::mutex* mutexToShare)
{
    sharedMutex = mutexToShare;
    //Non c' è bisogno di flag che mi dicano se il mutex è condiviso o no:
    //essendo un Poolable... mutex è condiviso per definizione
}



void RegistrablePoolableCyclicCallableSkeleton::operator()()
{
    while(true)
    {
        {
            boost::this_thread::disable_interruption disableInterruptions;
            {
                try
                {
                    boost::details::pool::guard<boost::mutex> mutexGuard(*sharedMutex);
                    socket = listeningSocket->acceptConnection();
                }
                catch(const SocketException& socketException)
                {
                    boost::this_thread::restore_interruption restoreInterruptions(disableInterruptions);
                    boost::this_thread::interruption_point();
                    break;
                }
            }
            protocol();
            delete socket;
            socket = NULL;
        }
        boost::this_thread::interruption_point();
    }
}
