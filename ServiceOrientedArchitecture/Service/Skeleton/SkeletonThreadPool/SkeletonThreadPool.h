#ifndef SKELETONTHREADPOOL_H
#define SKELETONTHREADPOOL_H

#include <boost/thread/thread.hpp>
#include <list>
#include <iostream>
using namespace std;

template <typename T, int poolSize> //T è un PoolableCallableSkeletonWrapper
class SkeletonThreadPool
{
protected:
    boost::thread_group pool;
    list<boost::thread*> threadReferences;
public:
    boost::mutex sharedMutex; //TODO orrore!!! Un membro dati pubblico!!! Rimediare!!!!
    TcpIpPassiveSocket sharedListeningSocket; //TODO orrore!!! Un membro dati pubblico!!! Rimediare!!!!
    SkeletonThreadPool(string IPAddress, int listeningPort, int backlog)
        : sharedListeningSocket(IPAddress, listeningPort, backlog)
    {
        cout << "SkeletonThreadPool<" << (typeid(T)).name() << ", " << poolSize << ">(" << listeningPort << ", " << backlog << ")" << endl;
        T callableObject;
        for(int i = 0; i < poolSize; i++)
        {
            threadReferences.push_front(new boost::thread(callableObject, &sharedMutex, &sharedListeningSocket));
            //Inserimento in O(1), la list non diventa owner del thread
            pool.add_thread(threadReferences.front);
            //Inserimento in O(1), il pool diventa owner del thread e ne farà la delete.
            //TODO il precedente statement viola l' incapsulamento. Un workaround?
            //NB: il pool prende ownership sul new thread, posso stare tranquillo per la delete
        }
    }
    virtual ~SkeletonThreadPool()
    {
        //TODO come elimino il socket?
        //TODO come evito i memory leak?
        pool.interrupt_all();
    }
};

#endif // SKELETONTHREADPOOL_H
