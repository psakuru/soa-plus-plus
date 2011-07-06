/**
 * @file SkeletonThreadPool.h
 * @author  Sacco Cosimo <cosimosacco@gmail.com>, Silvestri Davide <davidesil.web@gmail.com>
 *
 * @section LICENSE
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef SKELETONTHREADPOOL_H
#define SKELETONTHREADPOOL_H

#include <boost/thread/thread.hpp>
#include <list>
#include <iostream>
using namespace std;

/**
 * @class SkeletonThreadPool
 *
 * @brief Pool di thread specializzato nella gestione di skeleton.
 *
 * Uno SkeletonThreadPool gestisce un gruppo di skeleton che condividono un mutex ed un socket di listening.
 *
 */

template <typename T, int poolSize> //T è un PoolableCallableSkeletonWrapper
class SkeletonThreadPool
{
protected:
	/**
	 * Pool di thread boost.
	 */
    boost::thread_group pool;
	/**
	 * Lista di puntatori ai thread del pool.
	 */
    list<boost::thread*> threadReferences;
public:
	/**
	 * Lista di puntatori ai thread del pool.
	 */
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
            pool.add_thread(threadReferences.front());
            //Inserimento in O(1), il pool diventa owner del thread e ne farà la delete.
            //TODO il precedente statement viola l' incapsulamento. Un workaround?
            //NB: il pool prende ownership sul new thread, posso stare tranquillo per la delete
        }
    }
    virtual ~SkeletonThreadPool()
    {
        //TODO come elimino il socket?
        //TODO come evito i memory leak?
        ///TODO  sharedListeningSocket.close???
        pool.interrupt_all(); //TODO non ha effetto!!!! Sono tutti in zona non interrompibile! sia chi fa accept che chi è bloccato!
    }
};

#endif // SKELETONTHREADPOOL_H
