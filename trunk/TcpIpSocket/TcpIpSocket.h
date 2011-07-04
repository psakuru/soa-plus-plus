/**
 * @file TcpIpSocket.h
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

#ifndef TCPIPSOCKET_H
#define TCPIPSOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
using namespace std;

/**
 * @class TcpIpSocket
 *
 * @brief Socket TCP/IP.
 *
 * La classe astratta TcpIpSocket mantiene un descrittore di file relativo al socket gestito.
 */

class TcpIpSocket
{
protected:
    int socketDescriptor;
public:
	/**
	 * Costruttore. Crea il socket.
     */
    TcpIpSocket();
	/**
	 * Costruttore fittizio. Non istanzia alcun socket.
	 *
	 * @param NOP Prametro fittizio.
     */
    TcpIpSocket(int NOP);
	/**
	 * Distruttore. Chiude il socket. 
     */
    ~TcpIpSocket();
	/**
	 * Ritorna una rappresentazione ascii dell' indirizzo associato al socket.
	 *
	 * @return Indirizzo associato al socket.
     */
    virtual string getAddress() = 0;
};

#endif // TCPIPSOCKET_H
