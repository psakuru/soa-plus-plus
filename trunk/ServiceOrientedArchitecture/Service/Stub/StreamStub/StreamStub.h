/**
 * @file StreamStub.h
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

#ifndef STREAMSTUB_H
#define STREAMSTUB_H

#include "../Stub.h"
#include "../../../../SerializableObjects/Utilities/ByteArray/ByteArray.h"
#include "../../../../SerializableObjects/SerializationStrategies/SignalSerializationStrategy/ParticularSignals/BadRequestSerializationStrategy/BadRequestSerializationStrategy.h"

/**
 * @class StreamStub
 *
 * @brief Aggiunge all' interfaccia Stub degli operatori di bitwise shift.
 *
 * Aggiunge all' interfaccia Stub degli operatori di bitwise shift che semplificano l' inserimento di parametri consentendo l' uso di tipi base.
 * Inoltre, la direzione degli operatori viene utilizzata per specificare la direzione del parametro.
 * L' utilizzo di tipi semplici consente al programmatore dello stub finale (derivato da StreamStub) e all' utente finale di poter 
 * ignorare l' esistenza dei SerializableObject.
 *
 */

class StreamStub : public Stub
{
public:
    StreamStub();
    StreamStub(string serviceIDToSet, string serviceRegistryAddressToSet);
    virtual ~StreamStub();
    virtual void operator<<(int& value);
    virtual void operator<<(double& value);
    virtual void operator<<(string& value);
    virtual void operator<<(ByteArray& value);
    virtual void operator<<(BadRequestSignal& value);
    virtual void operator>>(int& value);
    virtual void operator>>(double& value);
    virtual void operator>>(string& value);
    virtual void operator>>(ByteArray& value);
    virtual void operator>>(BadRequestSignal& value);
};

#endif // STREAMSTUB_H
