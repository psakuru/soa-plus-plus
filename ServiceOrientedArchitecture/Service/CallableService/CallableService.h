/**
 * @file CallableService.h
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

#ifndef CALLABLE_SERVICE_H
#define CALLABLE_SERVICE_H

#include "../../../ObjectInterfaces/CallableObject/CallableObject.h"
#include "../Service.h"

/**
 * @class CallableService
 *
 * @brief Generico servizio invocabile.
 *
 * Un CallableService rappresenta un generico servizio invocabile.
 * CallableService è una classe template ottenuta per derivazione multipla, semplice dall' interfaccia CallableObject e virtuale dal proprio parametro template.
 * La derivazione virtuale dal parametro template è resa necessaria dal manifestarsi del problema del diamante in caso di derivazione multipla 
 * dal parametro template T (o una sua derivata) e da CallableService<T> (o una sua derivata).
 *
 * @pre Il parametro template deve riferirsi ad un tipo derivato da Service.
 */

template <typename T>
class CallableService : public CallableObject, virtual public T 
/*
* Esempio del verificarsi del problema del diamante:
* Skeleton <- CallableService<Skeleton>
* Skeleton <- RegistrableSkeleton
* RegistrableSkeleton + CallableSkeleton<Skeleton> <- RegistrableCallableSkeleton
*/
 {
public:
    CallableService() {}
    CallableService(string serviceIdToSet) : T(serviceIdToSet) {}
    CallableService(string serviceIdToSet, string ServiceRegistryToSet) : T(serviceIdToSet, ServiceRegistryToSet) {}
    virtual ~CallableService() {}
    virtual void operator()() = 0;
};

#endif // CALLABLE_SERVICE_H
