#include "Signal.h"

Signal::Signal()
{
    //ctor
}

uint64_t serialize(void** destinationBuffer)
{
    *destinationBuffer = malloc(sizeof(Type));
    *((Type*)(*destinationBuffer)) = objectType;
    return sizeof(Type);
}

void deserialize(void* bufferToUse)
    {
    signalHandler();
    }
