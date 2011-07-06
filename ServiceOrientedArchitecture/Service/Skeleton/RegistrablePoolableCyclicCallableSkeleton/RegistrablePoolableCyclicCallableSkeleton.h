/**
 * @file RegistrablePoolableCyclicCallableSkeleton.h
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

#ifndef POOLABLECYCLICCALLABLESKELETON_H
#define POOLABLECYCLICCALLABLESKELETON_H

#include "../Skeleton.h"
#include "../RegistrableSkeleton/RegistrableSkeleton.h"
#include "../../CallableService/CallableService.h"
#include "../../../../TcpIpSocket/TcpIpPassiveSocket/TcpIpPassiveSocket.h"
#include <boost/thread/mutex.hpp>

/**
 * @class RegistrablePoolableCyclicCallableSkeleton
 *
 * @brief Aggiunge ulteriori funzionalità all' interfaccia Skeleton.
 *
 * Aggiunge allo Skeleton la possibilità di essere invocato, di registrarsi, 
 * di essere inserito in un pool di skeleton e di effettuare il servizio ciclicamente. 
 *
 */

class RegistrablePoolableCyclicCallableSkeleton : public RegistrableSkeleton, public CallableService<Skeleton>
{
private:
	/**
	 * Mutex condiviso fra gli skeleton appartenenti al pool.
	 */ 
    boost::mutex* sharedMutex;
public:
    RegistrablePoolableCyclicCallableSkeleton(string serviceIDToSet); 
    virtual ~RegistrablePoolableCyclicCallableSkeleton();
	/**
	 * @param mutexToShare Mutex condiviso con il pool
	 */ 
    void shareMutex(boost::mutex* mutexToShare);
	/**
	 * Operatore di chiamata. 
	 * Ciclicamente, accetta una connessione sul socket ed esegue protocol().
	 */ 
    virtual void operator()();
};

#endif // POOLABLECYCLICCALLABLESKELETON_H
