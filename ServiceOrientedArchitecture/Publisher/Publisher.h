/**
 * @file Publisher.h
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

#ifndef SERVICEPUBLISHER_H
#define SERVICEPUBLISHER_H

#include "../Service/CallableService/CallableService.h"
#include "../Service/Stub/Stub.h"
#include "../../ObjectInterfaces/RegistrableObject/RegistrableObject.h"
#include <string>
using namespace std;

/**
 * Enumerato che definisce le modalità di funzionamento di un Publisher.
 * La modalità publish permette di registrare un oggetto registrabile su un Register.
 * La modalità censor permette di cancellare la registrazione effettuata su un Register.
 */
enum PublishingMode {publish, censor};

/**
 * @class Publisher
 *
 * @brief Servizio invocabile che permette di registrare/deregistrare un generico RegistrableObject.
 *
 * Un Publisher è un servizio invocabile che permette di registrare un generico RegistrableObject presso un Register e di deregistrarlo.
 * La lista degli oggetti da registrare/deregistrare, viene creata dinamicamente attraverso il metodo addObjectToPublish; l' operatore
 * di chiamata provvede a effettuare la registrazione/deregistrazione in accordo con la modalità di funzionamento settata attraverso
 * l' utilizzo del metodo setPublishingMode.
 * Il Publisher è un normale Stub che si riferisce ad un Servizio di registrazione/deregistrazione presente sul Register.
 * A differenza degli altri Stub, tuttavia, il protocollo di bind è semplificato poiché non c'è bisogno di chiedere al Register
 * l' indirizzo del ServiceProvider, essendo il Register stesso il ServiceProvider in questione.
 *
 */

class Publisher : public CallableService<Stub>
{
private:
	/**
	 * Resetta il serviceID dello stub Publisher e ripulisce la lista dei parametri di output.
	 */
	void resetStatus();
protected:
    PublishingMode publishingMode;
    void bind();
    string publishingModeToString(PublishingMode publishingModeToConvert);
public:
    Publisher(string RegistryAddress);
    virtual ~Publisher();
    void setPublishingMode(PublishingMode publishingModeToSet);
    void addObjectToPublish(RegistrableObject* objectToPublish);
    void operator()();
};

#endif // SERVICEPUBLISHER_H
