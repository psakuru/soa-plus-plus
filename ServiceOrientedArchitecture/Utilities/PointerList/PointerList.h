/**
 * @file PointerList.h
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

#ifndef POINTERLIST_H
#define POINTERLIST_H

#include <list>
using namespace std;

/**
 * @class PointerList
 *
 * @brief Generica lista di puntatori.
 *
 * Gestisce una generica lista di puntatori ad oggetti allocati in memoria dinamica.
 *
 */
template <typename T>
class PointerList : public list<T>
{
public:
    virtual ~PointerList()
    {
        typename list<T>::iterator i = this->begin();
        for(; i != this->end(); i++)
        {
            delete (*i);
        }
    }
	/**
	 * Elimina gli oggetti puntati.
	 */
    virtual void clear()
    {
        typename list<T>::iterator i = this->begin();
        while(i != this->end())
        {
            delete (*i); // Elimina l' oggetto puntato.
            i++;
            this->pop_front(); // Pop di un puntatore, non viene eliminato l' oggetto puntato.
        }
    }
	/**
	 * Cancella i puntatori ma non elimina gli oggetti puntati.
	 */
	virtual void popPointers()
	{
		int iterationsToEmptyList = (int)(this->size());
		for(int i = 0; i < iterationsToEmptyList; i++)
		{
			this->pop_front(); // Pop di un puntatore, non viene eliminato l' oggetto puntato.
		}
	}
};

#endif // POINTERLIST_H
