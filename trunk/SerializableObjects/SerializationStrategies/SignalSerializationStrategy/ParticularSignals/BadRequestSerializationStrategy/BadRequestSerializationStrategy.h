/**
 * @file BadRequestSerializationStrategy.h
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

#ifndef BADREQUEST_SERIALIZATION_STRATEGY_H
#define BADREQUEST_SERIALIZATION_STRATEGY_H

#include "../../SignalSerializationStrategy.h"
#include "../../Utilities/BadRequestSignal/BadRequestSignal.h"

/**
 * @class BadRequestSerializationStrategy
 *
 * @brief Esempio di Signal.
 *
 * La classe specializza il segnale di "bad request", un esempio di come trattare i segnali.
 *
 */

class BadRequestSerializationStrategy : public SignalSerializationStrategy
{
private:
    void signalHandler();
public:
    BadRequestSerializationStrategy();
    BadRequestSerializationStrategy(BadRequestSignal& userReference);
    Type getSignalType() const;
    int getValueLengthLength();
};

typedef BadRequestSerializationStrategy BadRequest;

#endif // BADREQUEST_SERIALIZATION_STRATEGY_H
