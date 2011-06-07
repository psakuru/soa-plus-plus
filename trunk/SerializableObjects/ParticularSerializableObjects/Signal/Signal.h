#ifndef SIGNAL_H
#define SIGNAL_H

#include "../../SerializableObject.h"
#include "../../TypeConstants.h"

class Signal : public SerializableObject
{
    private:
        static const Type objectType = SERIALIZABLE_SIGNAL;
        static const SignalType = 0;
        virtual void signalHandler() = 0;
    public:
        Signal();
        virtual ~Signal() = 0;
        virtual void operator=(const SerializableObject&);
        virtual Type getType() = 0;
        uint64_t serialize(void** destinationBuffer);
        void deserialize(void* bufferToUse);
};

#endif // SIGNAL_H
