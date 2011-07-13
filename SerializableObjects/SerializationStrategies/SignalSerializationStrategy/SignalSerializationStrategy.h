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

typedef int Fake; // E' un semplice segnale, quindi non necessita di una wrappedReference.

/**
 * @class SignalSerializationStrategy
 *
 * @brief Serializzazione di un segnale.
 *
 * La classe specializza il layer per serializzare i segnali. In particolare,
 * la classe definisce il protocollo di serializzazione e deserializzazione di un segnale.
 * Serializzare un segnale vuol dire salvare in un buffer le informazioni relative al
 * tipo di segnale (le uniche informazioni che un segnale trasmette).
 * La deserializzazione di un segnale comporta l' esecuzione del suo signal handler.
 * L' esistenza di segnali particolari è nascosta a livello di protocollo di serializzazione,
 * e diviene manifesta solo al livello successivo, quello del sotto-protocollo di serializzazione
 * contenuto nel campo value. Pertanto, i segnali hanno tutti uno stesso type, e solo a livello
 * di value diventano tangibili i diversi signalType, che permettono l' invocazione
 * degli adeguati signal handler.
 */

class SignalSerializationStrategy : public GenericSerializableReferenceLayer<Fake>
{
protected:
	/**
	 * Handler associato al particolare segnale.
	 */
    virtual void signalHandler() = 0;
public:
    SignalSerializationStrategy();
    Type getType() const;
	/**
	 * Ritorna il tipo del particolare segnale.
	 *
	 * @return Tipo del particolare segnale.
	 */
    virtual Type getSignalType() const = 0;
    int getValueLengthLength() = 0;
	/**
	 * La serializzazione produce un buffer con la seguente struttura:
	 * buffer := {header, value}, header := {type, valueLength}, value := {signalType}
	 *
	 * @param destinationBuffer
	 *
	 * @return Lunghezza del buffer.
	 */
    uint64_t serialize(void** destinationBuffer);
	/**
	 * La deserializzazione, in questo caso, comporta l' invocazione dell' handler associato al segnale.
	 *
	 * @param bufferToUse Parametro muto.
	 * @param length Parametro muto.
	 */
    void deserialize(uint64_t length, void* bufferToUse);
    string getValueTypeStringRepresentation();
};

typedef SignalSerializationStrategy Signal;

#endif // SIGNAL_SERIALIZATION_STRATEGY_H
