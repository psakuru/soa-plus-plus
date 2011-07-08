/**
 * @file MonitoredList.h
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

#ifndef MONITOREDLIST_H
#define MONITOREDLIST_H

#include <list>
#include <algorithm>
#include <boost/thread/shared_mutex.hpp>
#include <boost/thread/locks.hpp>
using namespace std;

/**
 * @class MonitoredList
 *
 * @brief TODO COMMENTARE!!!!!!Layer che garantisce la thread safety di una ExtensibleMap.
 *
 * TODO COMMENTARE!!!!!Il layer MonitoredExtensibleMap garantisce la thread safety di una ExtensibleMap proteggendo i 
 metodi 
 con opportune
 * guardie di mutua esclusione che operano secondo il paradigma Readers-Writers. In particolare i metodi di interfaccia
 * proteggono, all' interno dello scope delle guardie, l' invocazione di metodi di implementazione.
 *
 */

bool operator==(const ComparableString& a, const ComparableString& b);​

class ComparableString : public string
{
public:
	friend bool operator==(const ComparableString& a, const ComparableString& b);
};

bool operator==(const ComparableString& a, const ComparableString& b)
{
return (a.compare(b) == 0)? true : false;
}

class MonitoredList : list<T>
{
protected:
	boost::shared_mutex mutex;
	/**
	 * Metodo di implementazione della ricerca.
	 */
    virtual bool searchImplementation(T searchingKey);
	/**
	 * Metodo di implementazione dell' operazione di inserimento.
	 */
    virtual void insertElementImplementation(T elementToInsert);
	/**
	 * Metodo di implementazione dell' operazione di cancellazione.
	 */
    virtual void clearElementImplementation(T elementToClear);
    virtual void printImplementation();
public:
    virtual bool search(T searchingKey)
    {
        boost::shared_lock<boost::shared_mutex> readersLock(mutex);
        return this->end() != find_first_of(this->begin(), this->end(), searchingKey);
    virtual list<Element> get(Key searchingKey)
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

#endif // MONITOREDLIST_H
