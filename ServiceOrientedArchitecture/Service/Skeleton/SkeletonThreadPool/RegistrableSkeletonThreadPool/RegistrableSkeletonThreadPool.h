/**
 * @file RegistrableSkeletonThreadPool.h
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

#ifndef REGISTRABLESKELETONTHREADPOOL_H
#define REGISTRABLESKELETONTHREADPOOL_H

#include "../SkeletonThreadPool.h"
#include "../../Exceptions/EmptyPoolException.h"
#include <iostream>
using namespace std;

/**
 * @class RegistrableSkeletonThreadPool
 *
 * @brief Rende lo SkeletonThreadPool registrabile.
 *
 * Rende lo SkeletonThreadPool registrabile utilizzando l' interfaccia offerta da RegistrableObject.
 *
 */

template <typename T, int poolSize> class RegistrableSkeletonThreadPool
    : public RegistrableObject, public SkeletonThreadPool<T, poolSize>
{
public:
    RegistrableSkeletonThreadPool(string IPAddress, int listeningPort, int backlog)
        : SkeletonThreadPool<T, poolSize>(IPAddress, listeningPort, backlog) {}
	/**
	 * Ritorna le informazioni per la registrazione.
	 * Viene creato un oggetto del tipo T e vengono recuperate le informazioni di registrazione.
	 * Ad esse viene appeso l' indirizzo recuperato dal listening socket del thread pool.
	 */
    string getRegistrationInfo()
    {
		if(!SkeletonThreadPool<T, poolSize>::threadReferences.empty())
        {
            T dummyT;
            string registrationInfoToReturn = dummyT.getRegistrationInfo();
            registrationInfoToReturn.append(SkeletonThreadPool<T, poolSize>::sharedListeningSocket.getAddress());
			return registrationInfoToReturn;
        }
        else
        {
            throw EmptyPoolException();
        }
        return "<empty>";
    }
};

#endif // REGISTRABLESKELETONTHREADPOOL_H
