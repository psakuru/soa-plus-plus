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

/**
 * @class PoolableCallableSkeletonWrapper
 *
 * @brief Crea un PollableCallableSkeleton, lo inizializza correttamente e gli assegna le risorse condivise.
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
 * @pre Il parametro template T può essere un qualsiasi PoolableCallableSkeleton, con un costruttore di default
 * che inizializzi corretamente tutta la gerarchia. In particolare, è necessario che richiami il costruttore
 * con parametro serviceID della classe padre per permettere un' inizializzazione coerente.
 */

template <typename T>
class PoolableCallableSkeletonWrapper
{
public:
    void operator()(boost::mutex* sharedMutex, TcpIpPassiveSocket* sharedListeningSocket)
    {
        T poolableCallableSkeleton;
        poolableCallableSkeleton.shareMutex(sharedMutex);
        poolableCallableSkeleton.shareListeningSocket(sharedListeningSocket);
        poolableCallableSkeleton();
    }
};

#endif // POOLABLECALLABLESKELETONWRAPPER_H
