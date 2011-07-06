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
 * @brief Estende le funzionalità di uno Skeleton.
 *
 * TODO
 *
 */

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
