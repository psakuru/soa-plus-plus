#include "RegistrablePoolableCyclicCallableSkeleton.h"
#include <boost/thread/thread.hpp>
#include <boost/pool/detail/guard.hpp>
#include "../../../../TcpIpSocket/Exceptions/SocketException.h"

RegistrablePoolableCyclicCallableSkeleton::~RegistrablePoolableCyclicCallableSkeleton() {}

RegistrablePoolableCyclicCallableSkeleton::RegistrablePoolableCyclicCallableSkeleton(string serviceIDToSet)
    : Skeleton(serviceIDToSet), RegistrableSkeleton(serviceIDToSet), CallableService<Skeleton>(serviceIDToSet) {}

void RegistrablePoolableCyclicCallableSkeleton::shareMutex(boost::mutex* mutexToShare)
{
    sharedMutex = mutexToShare;
}

void RegistrablePoolableCyclicCallableSkeleton::operator()()
{
    while(true)
    {
        {
            boost::this_thread::disable_interruption disableInterruptions; // Altrimenti potrebbero verificarsi incoerenze nella gestione del socket
																		   // e/o nelle strutture dati manipolate in protocol().
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
                    return;
                }
            }
            protocol();
            delete socket;
            socket = NULL;
        }
        boost::this_thread::interruption_point();
    }
}
