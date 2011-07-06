/**
 * @file RegistrableSkeleton.h
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

#ifndef REGISTRABLESKELETON_H
#define REGISTRABLESKELETON_H

#include "../Skeleton.h"
#include "../../../../ObjectInterfaces/RegistrableObject/RegistrableObject.h"

/**
 * @class RegistrableSkeleton
 *
 * @brief Scheletro registrabile.
 *
 * Un RegistrableSkeleton è uno skeleton che implementa l' interfaccia offerta da RegistrableObject.
 * La derivazione virtuale da Skeleton è resa necessaria dal manifestarsi del problema del diamante in caso di derivazione multipla 
 * da Skeleton (o una sua derivata) e da RegistrableSkeleton (o una sua derivata).
 *
 */

class RegistrableSkeleton : public RegistrableObject, virtual public Skeleton
{
public:
    RegistrableSkeleton();
    RegistrableSkeleton(string serviceIDToSet);
    RegistrableSkeleton(string serviceIDToSet, TcpIpPassiveSocket* listeningSocketToShare);
	/**
	 * Le informazioni di registrazione hanno il seguente formato: "serviceID@IP:port"
	 */
    string getRegistrationInfo();
};

#endif // REGISTRABLESKELETON_H
