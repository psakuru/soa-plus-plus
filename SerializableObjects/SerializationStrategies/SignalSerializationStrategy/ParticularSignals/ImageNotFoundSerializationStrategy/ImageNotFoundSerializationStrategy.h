/**
 * @file ImageNotFoundSerializationStrategy.h
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

#ifndef IMAGENOTFOUND_SERIALIZATION_STRATEGY_H
#define IMAGENOTFOUND_SERIALIZATION_STRATEGY_H

#include "../../SignalSerializationStrategy.h"
#include "../../Utilities/ImageNotFoundSignal/ImageNotFoundSignal.h"
#include "../../Exceptions/ImageNotFoundException/ImageNotFoundException.h"

/**
 * @class ImagNotFoundSerializationStrategy
 *
 * @brief Segnale inviato in caso il server non possedesse l'immagine richiesta dal client.
 *
 */

class ImageNotFoundSerializationStrategy : public SignalSerializationStrategy
{
private:
    void signalHandler();
public:
    ImageNotFoundSerializationStrategy();
    ImageNotFoundSerializationStrategy(ImageNotFoundSignal& userReference);
    Type getSignalType() const;
    int getValueLengthLength();
};

typedef ImageNotFoundSerializationStrategy ImageNotFound;

#endif // IMAGENOTFOUND_SERIALIZATION_STRATEGY_H
