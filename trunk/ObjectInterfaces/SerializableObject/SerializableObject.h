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
#include "../../SerializableObjects/TypeConstants.h"
#include <string>
using namespace std;

/**
 * @class SerializableObject
 *
 * @brief Interfaccia per oggetti serializzabili.
 *
 * Gli oggetti serializzabili implementano l' interfaccia SerializableObject.
 *
 * Il protocollo di serializzazione è definito come segue: serializedObject := {header, value},
 * header := {type, valueLength}. Il campo value supporta un protocollo di serializzazione
 * di ordine superiore, secondo il modello ISO/OSI. Il campo type specifica il sotto-protocollo di
 * serializzazione adottato nel campo value. Esiste corrispondenza biunivoca tra sotto-protocollo
 * di serializzazione adottato e tipo di dati serializzato, pertanto si utilizza lo stesso
 * valore di type per indicare sia il tipo di dati serializzato che il sotto-protocollo di serializzazione
 * adottato.
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
    virtual Type getType() const = 0; // const perché lavora su un serializableObject const (quello passato con l' assegnamento).
    /**
     * Effettua la serializzazione secondo il protocollo.
     *
     * @param destinationBuffer Puntatore al buffer di destinazione.
     *
     * @return Lunghezza del buffer.
     */
    virtual uint64_t serialize(void** destinationBuffer) = 0;
    /**
     * Effettua la deserializzazione secondo il protocollo.
     *
     * @param length
     * @param bufferToUse
     *
     */
    virtual void deserialize(uint64_t length, void* bufferToUse) = 0;
    /**
     * Setta il valore dell' oggetto serializzabile.
     *
     * @param valueToSet
     *
     */
    virtual void setValue(void* valueToSet) = 0;
    /**
     * Ritorna il valore dell' oggetto serializzabile.
     *
     * @return Valore dell' oggetto serializzabile.
     *
     */
    virtual void* getValue() = 0;
    /**
     * Ritorna una rappresentazione human readable del tipo relativo all' oggetto serializzabile.
     *
     * @return Rappresentazione human readable del tipo dell' oggetto.
     *
     */
    virtual string getValueTypeStringRepresentation() = 0;
};

#endif // SERIALIZABLEOBJECT_H
