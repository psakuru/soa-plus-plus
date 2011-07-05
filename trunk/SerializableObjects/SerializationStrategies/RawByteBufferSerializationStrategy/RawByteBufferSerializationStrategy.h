/**
 * @file RawByteBufferSerializationStrategy.h
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

#ifndef RAWBYTEBUFFER_SERIALIZATION_STRATEGY_H
#define RAWBYTEBUFFER_SERIALIZATION_STRATEGY_H

#include "../../../ObjectInterfaces/SerializableObject/SerializableObject.h"
#include "../../Utilities/ByteArray/ByteArray.h"
#include "../../TypeConstants.h"
#include "../../GenericSerializableReferenceLayer/GenericSerializableReferenceLayer.h"

/**
 * @class RawByteBufferSerializationStrategy
 *
 * @brief Serializzazione di array di byte.
 *
 * La classe specializza il layer per trattare array di byte.
 *
 */

class RawByteBufferSerializationStrategy : public GenericSerializableReferenceLayer<ByteArray>
{
public:
	RawByteBufferSerializationStrategy();
    RawByteBufferSerializationStrategy(ByteArray& userReferenceToSet);
    RawByteBufferSerializationStrategy(ByteArray* userReferenceToSet, bool shared);
    Type getType() const;
    int getValueLengthLength();
    uint64_t serialize(void** destinationBuffer);
    void deserialize(uint64_t length, void* bufferToUse);
    string getValueTypeStringRepresentation();
};

typedef RawByteBufferSerializationStrategy RawByteBuffer;

#endif // RAWBYTEBUFFER_SERIALIZATION_STRATEGY_H
