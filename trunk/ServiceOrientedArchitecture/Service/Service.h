/**
 * @file Service.h
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

#ifndef SERVICE_H
#define SERVICE_H

#include "../Utilities/PointerList/PointerList.h"
#include "../../ObjectInterfaces/SerializableObject/SerializableObject.h"
#include "../../SerializableObjects/DeserializationStrategies/SerializableObjectBuilder.h"
#include "../../TcpIpSocket/TcpIpActiveSocket/TcpIpActiveSocket.h"
#include <string>
using namespace std;

/**
 * Lista di puntatori a SerializableObject, fa la delete sui puntatori quando distrutta.
 */
typedef PointerList<SerializableObject*> SerializableObjectList;

/**
 * Direzioni associate ai parametri. 
 * IN = parametro di input,
 * OUT = parametro di output,
 * INOUT = parametro di input da modificare e reinviare,
 * OUTIN = parametro di output da modificare e reinviare.
 */
enum Direction {IN, OUT, INOUT, OUTIN};

/**
 * @class Service
 *
 * @brief Generico servizio.
 *
 * Un Service rappresenta un generico servizio.
 *
 */

class Service
{
private:
	/**
	 * Metodo template che riceve dal socket il campo length (la lunghezza del campo value) e lo assegna al parametro valueLength.
	 * 
	 * @param valueLength
	 */
    template <typename IntegralFixedSizedType>
    void valueLengthReader(uint64_t& valueLength)
    {
        IntegralFixedSizedType* valueLengthPointer =
            (IntegralFixedSizedType*)socket->receiveMessage(sizeof(IntegralFixedSizedType));
        valueLength = *valueLengthPointer;
        free(valueLengthPointer);
    }
protected:
	/**
	 * Lista dei parametri di input.
	 */
    SerializableObjectList inputParameters;
	/**
	 * Lista dei parametri di output.
	 */
    SerializableObjectList outputParameters;
	/**
	 * Identificatore del servizio.
	 * Il formato è il seguente: serviceID; serviceID:={baseId(opt list parameter)}; parameter:={direction:type}; direction:={oneof IN, OUT, INOUT, OUTIN}; 
	 */
    string serviceID;
	/**
	 * Indirizzo del Service Registry.
	 */
    string serviceRegistryAddress;
	/**
	 * Socket su cui opera il servizio.
	 */
    TcpIpActiveSocket* socket;
	/**
	 * Radice dell' albero dei builder.
	 */
    SerializableObjectBuilder buildersHierarchy;
	/**
	 * Inizializzazione dell' albero dei builder.
	 */
    void defaultBuildersHierarchyInit();
	/**
	 * Invio dei parametri contenuti nella lista di output.
	 */
    virtual void sendParameters();
	/**
	 * Ricezioni dei parametri richiesti dalla lista di input.
	 */
    virtual void receiveParameters();
	/**
	 * Ricezione di un oggetto serializzato.
	 *
	 * @return Oggetto ricevuto.
	 */	
    SerializableObject* receiveParameter();
	/**
	 * Protocollo di comunicazione del particolare servizio.
	 */	
    virtual void protocol() = 0;
	/**
	 * Operazioni preliminari per il deploy del servizio.
	 */	
    virtual void bind() = 0;
	/**
	 * Aggiunge parameterToAdd ad una lista in base alla direzione specificata.
	 *
	 * @parameter parameterToAdd 
	 * @parameter parameterDirection
	 */
    virtual void addParameter(SerializableObject* parameterToAdd, Direction parameterDirection) = 0;
	/**
	 * Aggiorna il serviceID in base al parametro parameterToAdd e alla direzione specificata.
	 *
	 * @parameter parameterToAdd 
	 * @parameter parameterDirection
	 */
    void updateServiceID(SerializableObject* parameterToAdd, Direction parameterDirection);
public:
    Service();
    Service(string serviceIDToSet);
    virtual ~Service();
};

#endif // SERVICE_H

