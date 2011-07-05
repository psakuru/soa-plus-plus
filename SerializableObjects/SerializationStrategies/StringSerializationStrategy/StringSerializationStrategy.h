/**
 * @file StringSerializationStrategy.h
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

#ifndef STRING_SERIALIZATION_STRATEGY_H
#define STRING_SERIALIZATION_STRATEGY_H

#include "../../../ObjectInterfaces/SerializableObject/SerializableObject.h"
#include <string>
#include "../../TypeConstants.h"
#include "../../GenericSerializableReferenceLayer/GenericSerializableReferenceLayer.h"
using namespace std;

/**
 * @class StringSerializationStrategy
 *
 * @brief Serializzazione di una stringa.
 *
 * La classe specializza il layer per trattare le stringe.
 *
 */

class StringSerializationStrategy : public GenericSerializableReferenceLayer<string>
{
public:
	StringSerializationStrategy();
    StringSerializationStrategy(string& valueToSet);
    StringSerializationStrategy(string* valueToSet, bool shared);
    Type getType() const;
    int getValueLengthLength();
    uint64_t serialize(void** destinationBuffer);
    void deserialize(uint64_t length, void* bufferToUse);
    string getValueTypeStringRepresentation();
};

typedef StringSerializationStrategy String;

#endif // STRING_SERIALIZATION_STRATEGY_H
