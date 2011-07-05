/**
 * @file TerminalSerializableObjectBuilder.h
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

#ifndef TERMINALSERIALIZABLEOBJECTBUILDER_H
#define TERMINALSERIALIZABLEOBJECTBUILDER_H

#include "SerializableObjectBuilder.h"
#include <stdlib.h>
#include <typeinfo>

/**
 * @class TerminalSerializableObjectBuilder
 *
 * @brief Classe terminale del sistema di costruzione di SerializableObject.
 *
 * Classe terminale del sistema di costruzione di SerializableObject a partire dalla loro rappresentazione serializzata. 
 *
 *												SerializableObjectBuilder
 *												|					 |
 *               TerminalSerializableObjectBuilder<Integer>	...	 SignalBuilder
 *																	 |
 *												TerminalSerializableObjectBuilder<BadRequestSignalBuilder>
 *
 */

template <typename T>
class TerminalSerializableObjectBuilder : public SerializableObjectBuilder
{
public:
    int getValueLengthLength(Type receivedType)
    {
        T dummyT;
        return dummyT.getValueLengthLength(); //Se T non implementa l' interfaccia Serializable, questo fallisce a compile-time
    }
    SerializableObject* delegateBuilding(Type typeToBuild, uint64_t valueLength, void* value)
    {
        SerializableObject* serializableObjectToReturn = new T(); //NB: se T non deriva da SerializableObject, c' è un errore a compile-time
        serializableObjectToReturn->deserialize(valueLength, value);
        free(value);
        return serializableObjectToReturn;
    }
};

#endif // TERMINALSERIALIZABLEOBJECTBUILDER_H
