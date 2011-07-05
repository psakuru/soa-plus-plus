/**
 * @file SerializableObjectBuilder.h
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

#ifndef SERIALIZABLEOBJECTBUILDER_H
#define SERIALIZABLEOBJECTBUILDER_H

#include <map>
#include "../../ObjectInterfaces/SerializableObject/SerializableObject.h"
#include "../TypeConstants.h"
using namespace std;

/**
 * @class SerializableObjectBuilder
 *
 * @brief Classe base del sistema di costruzione di SerializableObject.
 *
 * Classe base del sistema di costruzione di SerializableObject a partire dalla loro rappresentazione serializzata. 
 *
 *												SerializableObjectBuilder
 *												|					 |
 *               TerminalSerializableObjectBuilder<Integer>	...	 SignalBuilder
 *																	 |
 *												TerminalSerializableObjectBuilder<BadRequestSignalBuilder>
 *
 */

class SerializableObjectBuilder
{
protected:
	/**
	 * Un builder mantiene una mappa che gli permette di delegare la costruzione di un SerializableObject a builder più specializzati.
	 * I puntatori sono collegamenti a nodi sottostanti.
	 */
    map< Type, SerializableObjectBuilder* > subSerializableObjectBuilders;
public:
    virtual ~SerializableObjectBuilder();
	/**
	 * Seleziona il builder specializzato nella costruzione di oggetti del tipo passato come parametro.
	 *
	 * @param builtType 
	 *
	 * @return 
	 */
    virtual SerializableObjectBuilder* operator[](Type builtType);
	/**
	 * Aggiunge un builder alla mappa.
	 * 
	 * @param builtType 
	 * @param builderToAdd
	 */
    virtual void addSerializableObjectBuilder(Type builtType, SerializableObjectBuilder* builderToAdd);
	/**
	 * Rimuove un builder dalla mappa.
	 * 
	 * @param builtType 
	 */
    virtual void removeSerializableObjectBuilder(Type builtType);
	/**
	 * Ritorna la lunghezza del campo length relativa alla rappresentazione serializzata del tipo da costruire.
	 * Tale informazione viene recuperata, in generale, richiedendola al builder più specializzato 
	 * che si trova in un livello inferiore della gerarchia dei builder, il quale potrebbe richiederla
	 * al livello sottostante, e così via...
	 * 
	 * @param receivedType 
	 * @return Lunghezza del campo length.
	 */
    virtual int getValueLengthLength(Type receivedType);
	/**
	 * Seleziona il builder specializzato nella costruzione di oggetti del tipo passato come parametro.
	 * Questo, a sua volta, può delegare la costruzione di tali oggetti al builder ancora più specializzato 
	 * che si trova in un livello inferiore della gerarchia dei builder, e così via...
	 * 
	 * @param builtType 
	 *
	 * @return SerializableObject richiesto.
	 */
    virtual SerializableObject* delegateBuilding(Type typeToBuild, uint64_t valueLength, void* value);
};


#endif // SERIALIZABLEOBJECTBUILDER_H
