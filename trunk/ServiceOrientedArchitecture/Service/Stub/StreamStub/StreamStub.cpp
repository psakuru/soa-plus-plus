#include "StreamStub.h"
#include "../../../../SerializableObjects/SerializationStrategies/IntegerSerializationStrategy/IntegerSerializationStrategy.h"
#include "../../../../SerializableObjects/SerializationStrategies/RealSerializationStrategy/RealSerializationStrategy.h"
#include "../../../../SerializableObjects/SerializationStrategies/StringSerializationStrategy/StringSerializationStrategy.h"
#include "../../../../SerializableObjects/SerializationStrategies/RawByteBufferSerializationStrategy/RawByteBufferSerializationStrategy.h"

StreamStub::StreamStub() {}

StreamStub::StreamStub(string serviceIDToSet, string serviceRegistryAddressToSet)
    : Stub(serviceIDToSet, serviceRegistryAddressToSet) {}

StreamStub::~StreamStub() {}

void StreamStub::operator<<(int& value)
{
    addParameter(new Integer(value), OUT);
}

void StreamStub::operator<<(double& value)
{
    addParameter(new Real(value), OUT);
}

void StreamStub::operator<<(string& value)
{
    addParameter(new String(value), OUT);
}

void StreamStub::operator<<(ByteArray& value)
{
    addParameter(new RawByteBuffer(value), OUT);
}

void StreamStub::operator<<(BadRequestSignal& value)
{
	addParameter(new BadRequest(value), OUT);
}

void StreamStub::operator<<(GenericSignalValue& value)
{
	addParameter(new GenericSignalWrapper(value), OUT);
}

void StreamStub::operator>>(int& value)
{
    addParameter(new Integer(value), OUTIN);
}

void StreamStub::operator>>(double& value)
{
    addParameter(new Real(value), OUTIN);
}

void StreamStub::operator>>(string& value)
{
    addParameter(new String(value), OUTIN);
}

void StreamStub::operator>>(ByteArray& value)
{
    addParameter(new RawByteBuffer(value), OUTIN);
}

void StreamStub::operator>>(BadRequestSignal& value)
{
    addParameter(new BadRequest(value), OUTIN);
}

void StreamStub::operator>>(GenericSignalValue& value)
{
    addParameter(new GenericSignalWrapper(value), OUTIN);
}
