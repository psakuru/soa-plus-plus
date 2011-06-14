#ifndef STREAMSTUB_H
#define STREAMSTUB_H

#include "../Stub.h"
#include "../../../../SerializableObjects/Utilities/ByteArray/ByteArray.h"
#include "../../../../SerializableObjects/SerializationStrategies/SignalSerializationStrategy/ParticularSignals/BadRequestSerializationStrategy/BadRequestSerializationStrategy.h"

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
