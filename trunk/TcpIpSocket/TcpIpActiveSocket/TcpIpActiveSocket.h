/**
 * @file TcpIpActiveSocket.h
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

#ifndef TCPIPACTIVESOCKET_H
#define TCPIPACTIVESOCKET_H

#include "../TcpIpSocket.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
using namespace std;

/**
 * @class TcpIpActiveSocket
 *
 * @brief Socket TCP/IP per comunicazione attiva.
 *
 * La classe TcpIpActiveSocket mantiene un descrittore di file relativo al socket attivo gestito.
 * Un socket attivo è un socket su cui si effettua una comunicazione attiva, a differenza di quanto accade quando si effettua l' operazione di listen.
 * Socket attivi sono socket su cui si fa la connect e socket ritornati dalla accept.
 */

class TcpIpActiveSocket : public TcpIpSocket
{
protected:
    sockaddr_in serverAddress;
public:
	/**
	 * Costruttore. Chiama la funzione connect sul socket.
	 *
	 * @param serverIPorURL
	 * @param port
     */
    TcpIpActiveSocket(string serverIPorURL, int port);
    /**
	 * Costruttore. Inizializza il socket attivo utilizzando il descrittore di file ritornato dalla funzione accept effettuata sul socket passivo passato come parametro.
	 *
     * @param listeningSocketDescriptor
	 */
	TcpIpActiveSocket(int listeningSocketDescriptor);
    /**
	 * Ritorna una rappresentazione human readable dell' indirizzo IP e della porta nel formato ip:porta.
	 *
	 * @return Stringa che rappresenta l' indirizzo IP e la porta sui quali il socket agisce.
     */
	string getAddress();
    /**
	 * Chiama la funzione send sul socket.
	 *
	 * @param buffer Buffer da inviare.
	 * @param length Lunghezza del buffer da inviare.
     */
	void sendMessage(void* buffer, uint64_t length);
    /**
	 * Chiama la funzione receive sul socket.
	 *
	 * @param length Lunghezza del buffer di ricezione.
	 *
	 * @return Buffer che ospita i byte ricevuti.
     */
	void* receiveMessage(uint64_t length);
};

#endif // TCPIPACTIVESOCKET_H
