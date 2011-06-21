#ifndef SKELETONTHREADPOOL_H
#define SKELETONTHREADPOOL_H

#include <boost/thread/thread.hpp>
#include <iostream>
using namespace std;

template <typename T, int poolSize> //T è un PoolableCallableSkeletonWrapper
class SkeletonThreadPool
{
private:
    boost::thread_group pool;
public:
    boost::mutex sharedMutex; //TODO orrore!!! Un membro dati pubblico!!! Rimediare!!!!
    TcpIpPassiveSocket sharedListeningSocket; //TODO orrore!!! Un membro dati pubblico!!! Rimediare!!!!
    SkeletonThreadPool(int listeningPort, int backlog)
        : sharedListeningSocket(listeningPort, backlog)
    {
        cout << "SkeletonThreadPool<" << (typeid(T)).name() << ", " << poolSize << ">(" << listeningPort << ", " << backlog << ")" << endl;
        T callableObject;
        for(int i = 0; i < poolSize; i++)
        {
            //cout << ">> SkeletonThreadPool: aggiungo un thread" << endl;
            pool.add_thread(new boost::thread(callableObject, &sharedMutex, &sharedListeningSocket));
            //TODO il precedente statement viola l' incapsulamento. Un workaround?
            //NB: il pool prende ownership sul new thread, posso stare tranquillo per la delete
        }
    }
    virtual ~SkeletonThreadPool()
    {
        //TODO come elimino il socket?
        pool.interrupt_all();
    }
};

#endif // SKELETONTHREADPOOL_H
