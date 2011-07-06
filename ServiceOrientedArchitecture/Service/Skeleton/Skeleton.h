/**
 * @file Skeleton.h
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

#ifndef SKELETON_H
#define SKELETON_H

#include "../Service.h"
#include "../../../TcpIpSocket/TcpIpPassiveSocket/TcpIpPassiveSocket.h"

/**
 * @class Skeleton
 *
 * @brief Scheletro.
 *
 * Uno Skeleton contiene le funzionalità di base che un servente deve possedere.
 *
 */

class Skeleton : public Service
{
protected:
	/**
	 * Socket passivo su cui il servente sta in ascolto.
	 */
    TcpIpPassiveSocket* listeningSocket;
    /**
	 * Flag che indica se il socket è condiviso o meno.
	 */	
    bool sharedListeningSocket;
    /**
	 * Attende richieste dal socket.
	 * Quando riceve una connessione, richiama il metodo protocol().
	 */
    void bind();
	/**
	 * Protocollo di comunicazione di un servente.
	 * Riceve i parametri in ingresso, effettuando un controllo sul numero e sui tipi.
	 * 
	 */	
    void protocol();
	/**
	 * Socket passivo su cui il servente sta in ascolto.
	 */	
    virtual void doService() = 0;
	/**
	 * Socket passivo su cui il servente sta in ascolto.
	 */	
    void addParameter(SerializableObject* parameterToAdd, Direction parameterDirection);
public:
    Skeleton();
    Skeleton(string serviceIDToSet);
    Skeleton(string serviceIDToSet, TcpIpPassiveSocket* listeningSocketToShare);
	/**
	 * Socket passivo su cui il servente sta in ascolto.
	 */	
    Skeleton(string serviceIDToSet, string IPAddress, int port, int backlog);
    virtual ~Skeleton();
	/**
	 * Socket passivo su cui il servente sta in ascolto.
	 */	
    void shareListeningSocket(TcpIpPassiveSocket* listeningSocketToShare);
};

#endif // SKELETON_H
