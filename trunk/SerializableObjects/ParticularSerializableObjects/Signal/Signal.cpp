#include "Signal.h"

Signal::Signal()
{
}

uint64_t serialize(void** destinationBuffer)
{
    *destinationBuffer = malloc(sizeof(Type));
    *((Type*)(*destinationBuffer)) = getType();
    return sizeof(Type);
}

void deserialize(uint64_t length, void* bufferToUse)
    {
    signalHandler();
    }
