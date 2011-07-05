/**
 * @file UnknownHostException.h
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

#ifndef UNKNOWNHOSTEXCEPTION_H
#define UNKNOWNHOSTEXCEPTION_H

#include <exception>

/**
 * @class UnknownHostException
 *
 * @brief Host non riconosciuto.
 *
 * L' eccezione indica che l' host non è stato riconosciuto.
 */

class UnknownHostException : public exception
{
public:
    virtual const char* what() const throw()
    {
        return "Cannot retrieve host from the specified URL/IP address.";
    }
};

#endif // UNKNOWNHOSTEXCEPTION_H