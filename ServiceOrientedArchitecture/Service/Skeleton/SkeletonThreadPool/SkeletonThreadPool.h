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
 * E' una classe template rispetto alla dimensione del pool ed al tipo di CallableObject.
 *
 */

template <typename T, int poolSize>
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
	boost::mutex sharedMutex; //TODO orrore!!! Un membro dati pubblico!!! Rimediare!!!! CHANGED
    TcpIpPassiveSocket sharedListeningSocket; //TODO orrore!!! Un membro dati pubblico!!! Rimediare!!!! CHANGED
public:
	/**
	 * Crea i thread, li inserisce nel pool e inserisce il puntatore al nuovo thread creato nella lista threadReferences.
	 */
    SkeletonThreadPool(string IPAddress, int listeningPort, int backlog)
        : sharedListeningSocket(IPAddress, listeningPort, backlog)
    {
		T callableObject;
        for(int i = 0; i < poolSize; i++)
        {
            threadReferences.push_front(new boost::thread(callableObject, &sharedMutex, &sharedListeningSocket)); // Inserimento in O(1), 
																												  // la list non diventa owner del thread
            pool.add_thread(threadReferences.front()); // Inserimento in O(1), il pool diventa owner del thread e ne farà la delete.
        }
    }
	/**
	 * Chiude il socket ed attende tutti i thread (la chiusura del socket comporta il lancio di una eccezione e la terminazione del thread).
	 */
    virtual ~SkeletonThreadPool()
    {
		sharedListeningSocket.closeSocket(); // Se i thread stavano utilizzando il socket, viene lanciata una eccezione e quindi vengono riabilitate le interruzioni.
		pool.join_all(); // Attendo che tutti i thread abbiano terminato.
	}
};

#endif // SKELETONTHREADPOOL_H
