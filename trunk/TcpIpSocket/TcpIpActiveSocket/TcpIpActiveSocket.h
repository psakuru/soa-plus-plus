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
 */

class TcpIpActiveSocket : public TcpIpSocket
{
protected:
    sockaddr_in serverAddress;
public:
    TcpIpActiveSocket(string serverIPorURL, int port);
    TcpIpActiveSocket(int listeningSocketDescriptor);
    string getAddress();
    void sendMessage(void* buffer, uint64_t length);
    void* receiveMessage(uint64_t length);
};

#endif // TCPIPACTIVESOCKET_H
