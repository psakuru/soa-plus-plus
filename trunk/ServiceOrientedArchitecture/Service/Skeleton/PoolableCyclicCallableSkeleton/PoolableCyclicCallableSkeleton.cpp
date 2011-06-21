#include "PoolableCyclicCallableSkeleton.h"
#include <boost/thread/thread.hpp>
#include <boost/pool/detail/guard.hpp>
#include <iostream>
using namespace std;

PoolableCyclicCallableSkeleton::PoolableCyclicCallableSkeleton(string serviceIDToSet)
    : CallableService<Skeleton>(serviceIDToSet)
{
    cout << "TID:" << boost::this_thread::get_id() << " PoolableCyclicCallableSkeleton(" << serviceIDToSet << ")" << endl << endl;
}

PoolableCyclicCallableSkeleton::~PoolableCyclicCallableSkeleton()
{
}

void PoolableCyclicCallableSkeleton::shareMutex(boost::mutex* mutexToShare)
{
    sharedMutex = mutexToShare;
    //Non c' è bisogno di flag che mi dicano se il mutex è condiviso o no:
    //essendo un Poolable... mutex è condiviso per definizione
}



void PoolableCyclicCallableSkeleton::operator()()
{
    //try
    //{
        while(true)
        {
            {
                boost::this_thread::disable_interruption disableInterruptions;
                //cout << ">> PoolableCyclicCallableSkeleton: cerco di fare la accept, se non posso mi blocco" << endl;
                {
                    boost::details::pool::guard<boost::mutex> mutexGuard(*sharedMutex);
                    //TODO try
                    //{
                    //cout << ">> PoolableCyclicCallableSkeleton: mi sono sbloccato, faccio la accept" << endl;
                    socket = listeningSocket->acceptConnection();
                    //cout << ">> Ho fatto la accept" << endl;
                    //}
                    //TODO catch(closedSocketException)
                    //{
                    //socket = NULL;
                    //mutex.unlock() non c'è bisogno se usi la guardia
                    //boost::this_thread::restore_interruption;
                    //boost::this_thread::interruption_point();
                    //}
                }
                //cout << ">> PoolableCyclicCallableSkeleton: col socket ottenuto esaudisco il protocollo" << endl;
                protocol();
                delete socket;
                socket = NULL;
            }
            boost::this_thread::interruption_point();
        }
    //}
    //catch(...) {}
}
