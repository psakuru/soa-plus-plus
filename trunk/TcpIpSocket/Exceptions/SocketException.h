/**
 * @file SocketException.h
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

#ifndef SOCKETEXCEPTION_H
#define SOCKETEXCEPTION_H

#include <exception>
#include <string.h>
#include <errno.h>

class SocketException : public exception
{
public:
	/**
	 * Specifica la tipologia di errore.
     */
    virtual const char* what() const throw()
    {
        return strerror(errno);
    }
};

#endif // SOCKETEXCEPTION_H
