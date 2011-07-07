/**
 * @file ExtensibleMap.h
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

#ifndef EXTENSIBLEMAP_H
#define EXTENSIBLEMAP_H

#include <map>
#include <list>
#include <utility>
using namespace std;

/**
 * @class ExtensibleMap
 *
 * @brief Interfaccia template per una generica mappa di liste template con gestione esplicita delle politiche di accesso agli elementi.
 *
 * Interfaccia template per una generica mappa di liste template con gestione esplicita delle politiche di accesso agli elementi.
 * L' operatore di selezione è pensato per implementare una politica di scheduling da definire nelle classi implementanti l' interfaccia.
 * La mappa a tal fine si compone di elementi generici. Chiave e valore, infatti, vengono realizzati attraverso tipi template. 
 * Il valore è una coppia formata da una lista di elementi e dalle informazioni necessarie alla loro schedulazione.
 *
 */
template <typename Key, typename SchedulingInformation, typename Element>
class ExtensibleMap
{
protected:
    map<Key, pair<SchedulingInformation, list<Element> > > dataStructure;
public:
    virtual Element operator[](Key searchingKey) = 0; //Ridà un elemento nella lista contenuta alla riga specificata secono le politiche di scheduling
    virtual list<Element> getAllElementsIn(Key searchingKey)
    {
        return dataStructure[searchingKey].second;
    }
    virtual void insertElement(Key selectingKey, Element elementToInsert) = 0;
    virtual void clearElement(Key selectingKey, Element elementToClear) = 0;
    virtual void clearElementList(Key selectingKey)
    {
        dataStructure.erase(selectingKey);
    }
};

#endif // EXTENSIBLEMAP_H
