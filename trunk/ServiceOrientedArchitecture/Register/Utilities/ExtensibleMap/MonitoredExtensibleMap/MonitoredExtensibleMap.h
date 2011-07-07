/**
 * @file MonitoredExtensibleMap.h
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

#ifndef MONITOREDEXTENSIBLEMAP_H
#define MONITOREDEXTENSIBLEMAP_H

#include "../ExtensibleMap.h"
#include <boost/thread/shared_mutex.hpp>
#include <boost/thread/locks.hpp>

/**
 * @class MonitoredExtensibleMap
 *
 * @brief Layer che garantisce la thread safety di una ExtensibleMap.
 *
 * Il layer MonitoredExtensibleMap garantisce la thread safety di una ExtensibleMap proteggendo i metodi con opportune
 * guardie di mutua esclusione che operano secondo il paradigma Readers-Writers. In particolare i metodi di interfaccia
 * proteggono, all' interno dello scope delle guardie, l' invocazione di metodi di implementazione.
 *
 */

template <typename Key, typename SchedulingInformation, typename Element>
class MonitoredExtensibleMap
    : public ExtensibleMap<Key, SchedulingInformation, Element>
{
protected:
	boost::shared_mutex mutex;
	/**
	 * Metodo di implementazione dell' operatore di selezione.
	 */
    virtual Element selectionOperatorImplementation(Key searchingKey, boost::upgrade_lock<boost::shared_mutex> upgradableLock) = 0;
	/**
	 * Metodo di implementazione dell' operazione di inserimento.
	 */
    virtual void insertElementImplementation(Key selectingKey, Element elementToInsert) = 0;
	/**
	 * Metodo di implementazione dell' operazione di cancellazione.
	 */
    virtual void clearElementImplementation(Key selectingKey, Element elementToClear) = 0;
public:
    virtual Element operator[](Key searchingKey)
    {
        boost::upgrade_lock<boost::shared_mutex> upgradableLock(this->mutex);
        return this->selectionOperatorImplementation(searchingKey, upgradableLock);
    }
    virtual list<Element> getAllElementsIn(Key searchingKey)
    {
        boost::shared_lock<boost::shared_mutex> readersLock(mutex);
        return this->dataStructure[searchingKey].second;
    }
    virtual void insertElement(Key selectingKey, Element elementToInsert)
    {
        boost::unique_lock<boost::shared_mutex> writersLock(mutex);
        this->insertElementImplementation(selectingKey, elementToInsert);
    }
    virtual void clearElement(Key selectingKey, Element elementToClear)
    {
        boost::unique_lock<boost::shared_mutex> writersLock(mutex);
        this->clearElementImplementation(selectingKey, elementToClear);
    }
    virtual void clearElementList(Key selectingKey)
    {
        boost::unique_lock<boost::shared_mutex> writersLock(mutex);
        this->dataStructure.erase(selectingKey);
    }
	/**
	 * Stampa la mappa.
	 */
    void print()
    {
        typename map<Key, pair<SchedulingInformation, list<Element> > >::iterator i = this->dataStructure.begin();
        for(; i != this->dataStructure.end(); i++)
        {
            cout << "[" << (*i).first << "]::";
            typename list<Element>::iterator j = (((*i).second).second).begin();
            for(; j != (((*i).second).second).end(); j++)
            {
                cout << "--->" << (*j);
            }
            cout << endl;
        }
    }
};

#endif // MONITOREDEXTENSIBLEMAP_H
