#ifndef SIGNAL_SERIALIZATION_STRATEGY_H
#define SIGNAL_SERIALIZATION_STRATEGY_H

#include "../../SerializableObject.h"
#include "../../TypeConstants.h"
#include "SignalTypeConstants.h"
#include "../../GenericSerializableReferenceLayer/GenericSerializableReferenceLayer.h"

typedef int Fake;

class SignalSerializationStrategy : public GenericSerializableReferenceLayer<Fake>
{
    protected:
        virtual void signalHandler() = 0;
    public:
        SignalSerializationStrategy();
        Type getType() const;
        virtual Type getSignalType() const = 0;
        int getValueLengthLength() = 0;
        uint64_t serialize(void** destinationBuffer);
        void deserialize(uint64_t length, void* bufferToUse);
};

typedef SignalSerializationStrategy Signal;

#endif // SIGNAL_SERIALIZATION_STRATEGY_H
