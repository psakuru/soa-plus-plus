/**
 * @file RRFIFOMonitoredExtensibleMap.h
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

#ifndef RRFIFOMONITOREDEXTENSIBLEMAP_H
#define RRFIFOMONITOREDEXTENSIBLEMAP_H

#include "../MonitoredExtensibleMap.h"
#include <iostream>
using namespace std;

/**
 * @class RRFIFOMonitoredExtensibleMap
 *
 * @brief Implementa la politica di scheduling RoundRobin e l' inserimento di tipo FIFO.
 *
 * La classe template RRFIFOMonitoredExtensibleMap implementa una gestione della mappa FIFO negli inserimenti e RoundRobin nella selezione.
 * SchedulingInformation è in questo caso un semplice intero che identifica il prossimo elemento della lista da schedulare.
 *
 */

template <typename Key, typename Element>
class RRFIFOMonitoredExtensibleMap
    : public MonitoredExtensibleMap<Key, int, Element>
{
protected:
    Element selectionOperatorImplementation(Key searchingKey)
    {
        // In questa particolare politica la selezione comporta una modifica delle
        // scheduling information: il mutex va upgradato a unique lock!
		boost::upgrade_lock<boost::shared_mutex> writersLock(this->mutex);
        if(this->dataStructure.find(searchingKey) == this->dataStructure.end())
        {
            return Element();
        }
        if(this->dataStructure[searchingKey].second.size() == 0)
        {
            return Element();
        }
        typename list<Element>::iterator i = this->dataStructure[searchingKey].second.begin();
        for(int j = 0; j < this->dataStructure[searchingKey].first; j++)
        {
            i++;
        }
        this->dataStructure[searchingKey].first = (this->dataStructure[searchingKey].first+1)%((int)this->dataStructure[searchingKey].second.size());
		return *i;
    }
    void insertElementImplementation(Key searchingKey, Element elementToInsert)
    {
        if(this->dataStructure[searchingKey].second.empty())
        {
            this->dataStructure[searchingKey].first = 0;
        }
        this->dataStructure[searchingKey].second.push_back(elementToInsert);
    }
    void clearElementImplementation(Key selectingKey, Element elementToClear)
    {
        if(this->dataStructure.find(selectingKey) == this->dataStructure.end()) return;
        if(this->dataStructure[selectingKey].second.size() == 0) return;
        typename list<Element>::iterator i = this->dataStructure[selectingKey].second.begin();
		int j = 0;
        while((i != (this->dataStructure[selectingKey].second.end())) && ((*i).compare(elementToClear) != 0))
        {
            i++;
			j++;
        }
        if(i != this->dataStructure[selectingKey].second.end()) // Se l' elemento da eliminare esiste.
        {
            this->dataStructure[selectingKey].second.erase(i);
			// Aggiorno la SchedulingInformation per implementare la politica RR.
			if(this->dataStructure[selectingKey].first <= j){
				if(this->dataStructure[selectingKey].first == ((int)(this->dataStructure[selectingKey].second.size())))
				// Se l'elemento cancellato occupava l'ultima posizione della lista ed era selezionato come il prossimo da schedulare,
				// il prossimo elemento da schedulare dovrà essere quello in posizione 0.
				{
					this->dataStructure[selectingKey].first = 0;
				}
			}
			else // Se l'elemento cancellato precedeva la posizione del prossimo elemento da schedulare, l' indice relativo al prossimo
				 // elemento da schedulare dovrà essere aggiornato alla posizione precedente cioè alla nuova posizione assunta dal prossimo
				 // elemento da schedulare a causa dell' accorciamento della lista.
			{
				this->dataStructure[selectingKey].first --;
			}
        }
        else return;
    }
};

#endif // RRFIFOMONITOREDEXTENSIBLEMAP_H
