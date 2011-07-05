/**
 * @file SignalSerializationStrategy.h
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

#ifndef SIGNAL_SERIALIZATION_STRATEGY_H
#define SIGNAL_SERIALIZATION_STRATEGY_H

#include "../../../ObjectInterfaces/SerializableObject/SerializableObject.h"
#include "../../TypeConstants.h"
#include "SignalTypeConstants.h"
#include "../../GenericSerializableReferenceLayer/GenericSerializableReferenceLayer.h"

typedef int Fake;

/**
 * @class SignalSerializationStrategy
 *
 * @brief Serializzazione di un segnale.
 *
 * 
 *
 */

class SignalSerializationStrategy : public GenericSerializableReferenceLayer<Fake>
{
protected:
	/**
	 * Gestisce le conseguenze dell' arrivo di un segnale.
	 */
    virtual void signalHandler() = 0;
public:
    SignalSerializationStrategy();
    Type getType() const;
    virtual Type getSignalType() const = 0;
    int getValueLengthLength() = 0;
    uint64_t serialize(void** destinationBuffer);
	/**
	 * La deserializzazione, in questo caso, maschera l' invocazione dell' handler.
	 */
    void deserialize(uint64_t length, void* bufferToUse);
    string getValueTypeStringRepresentation();
};

typedef SignalSerializationStrategy Signal;

#endif // SIGNAL_SERIALIZATION_STRATEGY_H
