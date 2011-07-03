#ifndef POOLABLECALLABLESKELETONWRAPPER_H
#define POOLABLECALLABLESKELETONWRAPPER_H

#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>

template <typename T>
class PoolableCallableSkeletonWrapper
{
public:
    void operator()(boost::mutex* sharedMutex, TcpIpPassiveSocket* sharedListeningSocket)
    {


        cout << "TID:" << boost::this_thread::get_id() << " PoolableCallableSkeletonWrapper<" << (typeid(T)).name() << ">(sharedMutex: " << (void*)sharedMutex << ", sharedListeningSocket: " << (void*)sharedListeningSocket << ")" << endl;
        T poolableCallableSkeleton; //Precondizione: il costruttore di default di T deve soddisfare tutti gli antenati
        poolableCallableSkeleton.shareMutex(sharedMutex); //Può fallire solo a tempo di compilazione!
        poolableCallableSkeleton.shareListeningSocket(sharedListeningSocket); //Può fallire solo a tempo di compilazione!
        poolableCallableSkeleton(); //Può fallire solo a tempo di compilazione!*/
        //Se i precedenti tre statement non falliscono, allora o T è effettivamente figlio di Skeleton
        //oppure funziona come uno Skeleton, ma...
        //TODO polimorphic test!
    }
};

#endif // POOLABLECALLABLESKELETONWRAPPER_H
