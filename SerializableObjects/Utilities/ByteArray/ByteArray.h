/**
 * @file ByteArray.h
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

#ifndef BYTEARRAY_H
#define BYTEARRAY_H

#include <stdint.h>

typedef uint8_t byte;

/**
 * @class ByteArray
 *
 * @brief Array di byte.
 *
 * ByteArray gestisce array di byte.
 *
 */

class ByteArray
{
private:
    byte* byteArray;
    uint64_t length;
public:
    ByteArray();
	virtual ~ByteArray();
	/*
	 * Costruttore. Costruisce un byte array copiando il contenuto del byte array passato come parametro.
	 *
	 * @param byteArrayToCopy
	 */
    ByteArray(const ByteArray& byteArrayToCopy);
	/*
	 * Costruttore. Costruisce un byte array vuoto di lunghezza length.
	 *
	 * @param length
	 */
    ByteArray(uint64_t length);
	/*
	 * Costruttore. Costruisce un byte array copiando il contenuto del byte array passato come parametro per una lunghezza pari a length.
	 *
	 * @param byteArrayToSet
	 * @param lengthToSet
	 */
    ByteArray(void* byteArrayToSet, uint64_t lengthToSet);
	/*
	 * Ritorna il byte alla posizione index.
	 *
	 * @param index
	 * @return Byte richiesto per riferimento.
	 */
    byte& operator[](const uint64_t index); // Viola l' incapsulamento
	/*
	 * Ritorna il byte alla posizione index.
	 *
	 * @param index
	 * @return Byte richiesto per riferimento.
	 */
    void operator=(const ByteArray& byteArrayToCopy);
    void erase();
    void append(byte* bufferToUse, uint64_t startingPosition, uint64_t fragmentLength);
    uint64_t getLength();
    const byte* getPointer();
};

#endif // BYTEARRAY_H
