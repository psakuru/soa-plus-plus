#include "RegistrablePoolableCyclicCallableSkeleton.h"
#include <boost/thread/thread.hpp>
#include <boost/pool/detail/guard.hpp>
#include "../../../../TcpIpSocket/Exceptions/SocketException.h"
#include <iostream>
using namespace std;

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
					socket = NULL;
                    socket = listeningSocket->acceptConnection();
                }
                catch(const SocketException& socketException)
                {
                    delete socket;
                    socket = NULL;
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
