/**
 * @file IntegerSerializationStrategy.h
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

#ifndef INTEGER_SERIALIZATION_STRATEGY_H
#define INTEGER_SERIALIZATION_STRATEGY_H

#include <stdint.h>
#include "../../TypeConstants.h"
#include "../../../ObjectInterfaces/SerializableObject/SerializableObject.h"
#include "../../GenericSerializableReferenceLayer/GenericSerializableReferenceLayer.h"

/**
 * @class IntegerSerializationStrategy
 *
 * @brief Serializzazione di un intero.
 *
 * La classe specializza il GenericSerializableReferenceLayer per trattare gli interi.
 *
 */

class IntegerSerializationStrategy : public GenericSerializableReferenceLayer<int32_t>
{
public:
	IntegerSerializationStrategy();
    IntegerSerializationStrategy(int32_t& valueToSet);
    IntegerSerializationStrategy(int32_t* userReferenceToSet, bool shared);
    Type getType() const;
    int getValueLengthLength();
    uint64_t serialize(void** destinationBuffer);
    void deserialize(uint64_t length, void* bufferToUse);
    string getValueTypeStringRepresentation();
};

typedef IntegerSerializationStrategy Integer;

#endif // INTEGER_SERIALIZATION_STRATEGY_H
