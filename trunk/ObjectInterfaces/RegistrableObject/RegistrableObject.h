#ifndef REGISTRABLEOBJECT_H
#define REGISTRABLEOBJECT_H

#include <string>
using namespace std;

/**
 * @file RegistrableObject.h
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
 * @section DESCRIPTION
 *
 * L' interfaccia RegistrableObject fornisce, alle classi che la implementano, il metodo "getRegistrationInfo()".
 */

class RegistrableObject
{
public:
    /**
	 * Il metodo consente di ottenere dalla classe che implementa l'interfaccia le informazioni relative alla registrazione.
     * 
     * @param  
     * 
     * @return Informazioni relative alla registrazione.
     */
    virtual string getRegistrationInfo() = 0;
};

#endif // REGISTRABLEOBJECT_H
