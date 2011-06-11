#ifndef SIGNAL_H
#define SIGNAL_H

#include "../../SerializableObject.h"
#include "../../TypeConstants.h"
#include "SignalTypeConstants.h"


class Signal : public SerializableObject
{
    private:
        virtual void signalHandler() = 0;
    public:
        Signal();
        virtual ~Signal();
        virtual void operator=(const SerializableObject&) = 0;
        virtual Type getType() = 0;
        int getValueLengthLength() = 0;
        uint64_t serialize(void** destinationBuffer);
        void deserialize(uint64_t length, void* bufferToUse);
        void setValue(void* valueToSet);
        void* getValue();
};

#endif // SIGNAL_H
