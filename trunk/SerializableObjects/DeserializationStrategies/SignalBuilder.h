/**
 * @file SignalBuilder.h
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

#ifndef SIGNALBUILDER_H
#define SIGNALBUILDER_H

#include "SerializableObjectBuilder.h"

/**
 * @class SignalBuilder
 *
 * @brief Classe intermedia del sistema di costruzione di SerializableObject.
 *
 * Classe intermedia del sistema di costruzione di SerializableObject a partire dalla loro rappresentazione serializzata. 
 *
 *												SerializableObjectBuilder
 *												|					 |
 *               TerminalSerializableObjectBuilder<Integer>	...	 SignalBuilder
 *																	 |
 *												TerminalSerializableObjectBuilder<BadRequestSignalBuilder>
 *
 */

class SignalBuilder : public SerializableObjectBuilder
{
public:
    SignalBuilder();
    virtual ~SignalBuilder();
	/**
	 * Il metodo ritorna direttamente la lunghezza del campo length associato alla rappresentazione serializzta di un segnale.
	 *
	 * @param receivedType
	 *
	 * @return Lunghezza del campo length.
	 */	
    int getValueLengthLength(Type receivedType);
	/**
	 * Seleziona il builder specializzato nella costruzione di segnali del tipo passato attraverso il parametro value.
	 * Questo, a sua volta, può delegare la costruzione di tali segnali al builder ancora più specializzato 
	 * che si trova in un livello inferiore della gerarchia dei builder, e così via...
	 * 
	 * @param typeToBuild 
	 * @param valueLength 
	 * @param value
	 *
 	 * @return Puntatore ad un oggetto derivato da SerializableObject allocato in memoria dinamica.
	 *
	 * @post Il chiamante diventa owner dell' oggetto ritornato. Deve quindi occuparsi di liberare la memoria dinamica occupata quando opportuno.
	 */
    virtual SerializableObject* delegateBuilding(Type typeToBuild, uint64_t valueLength, void* value);
};

#endif // SIGNALBUILDER_H
