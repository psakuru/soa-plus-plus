/**
 * @file SingletonObject.h
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

#ifndef SINGLETONOBJECT_H
#define SINGLETONOBJECT_H

#include <boost/thread/mutex.hpp>
#include <boost/pool/detail/guard.hpp>


/**
 * @class SingletonObject
 *
 * @brief Le classi che implementano l' interfaccia SingletonObject possono essere istanziate una sola volta, secondo il design pattern Singleton.
 *
 * Le classi che implementano l' interfaccia SingletonObject possono essere istanziate una sola volta, secondo il design pattern Singleton.
 */

template <typename T>
class SingletonObject
{
private:
    static T* instance;
    static boost::mutex lifecycleControl;
    SingletonObject() {}
    ~SingletonObject() {}
public:
    static T* getInstance()
    {
        boost::details::pool::guard<boost::mutex> lifecycleGuard(lifecycleControl);
        if(instance == NULL) instance = new T();
        return instance;
    }
    static void destroyInstance()
    {
        boost::details::pool::guard<boost::mutex> lifecycleGuard(lifecycleControl);
        delete instance;
        instance = NULL;
    }
};

template <typename T> T* SingletonObject<T>::instance = NULL;
template <typename T> boost::mutex SingletonObject<T>::lifecycleControl;

#endif //SINGLETONOBJECT_H
