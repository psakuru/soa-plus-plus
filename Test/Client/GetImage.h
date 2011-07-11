/**
 * @file GetImage.h
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

#include "../../ServiceOrientedArchitecture/Service/Stub/StreamStub/StreamStub.h"
#include "../../SerializableObjects/SerializationStrategies/SignalSerializationStrategy/Utilities/GenericSignalValue/GenericSignalValue.h"
#include "../../SerializableObjects/SerializationStrategies/SignalSerializationStrategy/ParticularSignals/ImageNotFoundSerializationStrategy/ImageNotFoundSerializationStrategy.h"
#include "../../SerializableObjects/DeserializationStrategies/TerminalSerializableObjectBuilder.h"
#include <string>
using namespace std;

class GetImage: public StreamStub {
public:
	GetImage() : StreamStub("GetImage", "127.0.0.1:4000")
	{
		// Si aggiunge alla gerarchia dei builders il builder necessario alla costruzione del particolare segnale richiesto.
		buildersHierarchy[SERIALIZABLE_SIGNAL]->addSerializableObjectBuilder(SIGNAL_IMAGENOTFOUND, new TerminalSerializableObjectBuilder<ImageNotFound>());
	}
	GetImage(string serviceRegistryToSet) : StreamStub("GetImage", serviceRegistryToSet)
	{
		// Si aggiunge alla gerarchia dei builders il builder necessario alla costruzione del particolare segnale richiesto.
		buildersHierarchy[SERIALIZABLE_SIGNAL]->addSerializableObjectBuilder(SIGNAL_IMAGENOTFOUND, new TerminalSerializableObjectBuilder<ImageNotFound>());
	}
	void operator()(string name, ByteArray& img)
	{
		GenericSignalValue signal; // Il servizio attende l' arrivo di un segnale in risposta dal server
		(*this) << name; (*this) >> img; (*this) >> signal;
		bind();
		protocol();
	}
};
