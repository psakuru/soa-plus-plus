/**
 * @file PoolableCallableSkeletonWrapper.h
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

#ifndef POOLABLECALLABLESKELETONWRAPPER_H
#define POOLABLECALLABLESKELETONWRAPPER_H

#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>

/**
 * @class PoolableCallableSkeletonWrapper
 *
 * @brief 
 *
 * Un PoolableCallableSkeletonWrapper è un oggetto invocabile che crea un PollableCallableSkeleton,
 * lo inizializza correttamente e gli assegna le risorse condivise.
 * Ciò è reso necessario per ovviare all' inconveniente di dotare un PoolableCallableSkeleton di 
 * un costruttore di copia, richiamato alla creazione del thread, che sarebbe molto complesso 
 * e dispendioso: richiederebbe una deep copy di liste di parametri
 * formate da SerializableObject, copia di Socket con le relative possibili incoerenze etc...
 * In questo modo, invece, la creazione del PoolableCallableSkeleton è rinviata all' esecuzione del thread,
 * ed effettuata attraverso semplici costruttori.
 * 
 */

template <typename T>
class PoolableCallableSkeletonWrapper
{
public:
    void operator()(boost::mutex* sharedMutex, TcpIpPassiveSocket* sharedListeningSocket)
    {
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
