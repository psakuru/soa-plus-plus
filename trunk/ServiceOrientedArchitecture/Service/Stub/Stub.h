/**
 * @file Stub.h
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

#ifndef STUB_H
#define STUB_H

#include "../Service.h"

/**
 * @class Stub
 *
 * @brief Stub.
 *
 * Uno stub è un' interfaccia locale che rappresenta un servizio remoto presso il client.
 *
 */

class Stub : public Service
{
protected:
    string serviceProviderAddress;
	/**
	 * Richiede al Register l' indirizzo del serviceProvider ed effettua la connessione.
	 */
    virtual void bind();
	/**
	 * Protocollo di comunicazione dello Stub.
	 * Il protocollo consiste nell' invio di entrambe le liste, quella di input e quella di output e nella ricezione dei parametri di output.
	 */
	void protocol();
    void addParameter(SerializableObject* parameterToAdd, Direction parameterDirection);
public:
    Stub();
    Stub(string serviceIDToSet, string serviceRegistryAddressToSet);
    virtual ~Stub();
    string getServiceRegistryAddress();
    void setServiceRegistryAddress(string serviceRegistryAddressToSet);
	/**
	 * Rieffettua la bind.
	 * Necessaria in caso di modifiche al serviceRegistryAddress.
	 */
    void rebind();
	/**
	 * Consente di impostare staticamente l' indirizzo del serviceProvider, evitando il protocollo di richiesta al Register.
	 *
	 * @parameter serviceProviderAddressToSet
	 */
    void staticallyBind(string serviceProviderAddressToSet);
};

#endif // STUB_H
