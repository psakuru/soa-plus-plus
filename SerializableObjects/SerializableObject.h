/**
 * @file SerializableObject.h
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

#ifndef SERIALIZABLEOBJECT_H
#define SERIALIZABLEOBJECT_H

#include <stdint.h>
#include "TypeConstants.h"
#include <string>
using namespace std;

/**
 * @class SerializableObject
 *
 * @brief Interfaccia per oggetti serializzabili.
 *
 * Gli oggetti serializzabili implementano l' interfaccia SerializableObject.
 *
 * Il protocollo di serializzazione è definito come segue:
 *
 *                      serialize
 *                          |
 *	OggettoSerializzabile  --->	[  type  |  length  |  value  ]
 *
 */

class SerializableObject
{
public:
	/**
	 * Distruttore virtuale puro.
     */
    virtual ~SerializableObject() = 0;
	/**
	 * Operatore assegnamento.
	 *
	 * @param serializableObjectToBeAssigned
     */
    virtual void operator=(const SerializableObject& serializableObjectToBeAssigned) = 0;
	/**
	 * Ritorna la lunghezza del campo length (lunghezza del campo value).
     *
	 * @return Lunghezza del campo length.
     */
    virtual int getValueLengthLength() = 0;
	/**
	 * Ritorna il tipo dell' oggetto serializzabile.
     *
	 * @return Tipo di oggetto serializzabile.
     */
    virtual Type getType() const = 0;
	/**
	 * Effettua la serializzazione secondo il protocollo. 
     *
	 * @param destinationBuffer  
	 *
	 * @return Lunghezza del campo length.
     */
    virtual uint64_t serialize(void** destinationBuffer) = 0; //TODO fare tutta sta roba (x cosimo: serializzazione del tipo e della lunghezza) 
															  // quì invece che nelle derivate, tanto è sempre uguale
    virtual void deserialize(uint64_t length, void* bufferToUse) = 0;
    virtual void setValue(void* valueToSet) = 0;
    virtual void* getValue() = 0;
    virtual string getValueTypeStringRepresentation() = 0;
};

#endif // SERIALIZABLEOBJECT_H
