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
	 * Metodo template che riceve dal socket la lunghezza del campo valore e la assegna al parametro valueLength.
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
    SerializableObjectList inputParameters;
    SerializableObjectList outputParameters;
    string serviceID;
    string serviceRegistryAddress;
    TcpIpActiveSocket* socket;
    SerializableObjectBuilder buildersHierarchy;
    void defaultBuildersHierarchyInit();
    virtual void sendParameters();
    virtual void receiveParameters();
    SerializableObject* receiveParameter();
    virtual void protocol() = 0;
    virtual void bind() = 0;
    virtual void addParameter(SerializableObject* parameterToAdd, Direction parameterDirection) = 0;
    void updateServiceID(SerializableObject* parameterToAdd, Direction parameterDirection);
public:
    Service();
    Service(string serviceIDToSet);
    virtual ~Service();
};

#endif // SERVICE_H

