/**
 * @file TcpIpPassiveSocket.h
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

#ifndef TCPIPPASSIVESOCKET_H
#define TCPIPPASSIVESOCKET_H

#include "../TcpIpActiveSocket/TcpIpActiveSocket.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

/**
 * @class TcpIpPassiveSocket
 *
 * @brief Socket TCP/IP che accetta richieste di connessione.
 *
 * La classe TcpIpPassiveSocket mantiene un descrittore di file relativo al socket passivo gestito.
 * Un socket passivo è un socket su cui si effettua l' operazione di listen.
 *
 */

class TcpIpPassiveSocket : public TcpIpSocket
{
protected:
    sockaddr_in serverAddress;
public:
	/**
	 * Costruttore. Effettua la listen sul socket.
	 *
	 * @param IPAddress
	 * @param listeningPort
	 * @param backlog Numero massimo di connessioni pendenti.
     */
    TcpIpPassiveSocket(string IPAddress, int listeningPort, int backlog);
	/**
	 * Ritorna il socket attivo (su cui è stata eseguita la accept).
	 *
	 * @return Socket attivo (il cui costruttore ha eseguito la accept).
     */
    TcpIpActiveSocket* acceptConnection();
	/**
	 * Ritorna una rappresentazione human readable dell' indirizzo IP e della porta nel formato ip:porta.
	 *
	 * @return Stringa che rappresenta l' indirizzo IP e la porta sui quali il socket agisce.
     */
    string getAddress();
	/**
	 * Chiude il socket.
	 */
	void shutdownSocket();
};

#endif // TCPIPPASSIVESOCKET_H
