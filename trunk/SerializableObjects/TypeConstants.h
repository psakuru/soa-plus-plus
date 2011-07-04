/**
 * @file TypeConstants.h
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
 * @section DESCRIPTION
 * Il file contiene la definizione di costanti che identificano i tipi serializzabili.
 */

#ifndef TYPECONSTANTS_H_INCLUDED
#define TYPECONSTANTS_H_INCLUDED

#define SERIALIZABLE_OBJECT 0
#define SERIALIZABLE_INTEGER 1
#define SERIALIZABLE_REAL 2
#define SERIALIZABLE_STRING 3
#define SERIALIZABLE_RAW_BYTE_BUFFER 4
#define SERIALIZABLE_SIGNAL 5
typedef int Type;

#endif // TYPECONSTANTS_H_INCLUDED
