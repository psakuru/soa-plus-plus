#include "Signal.h"
#include <stdlib.h>

Signal::Signal()
{
userReference = false;
}

Signal::~Signal()
{
}

uint64_t Signal::serialize(void** destinationBuffer)
{
    *destinationBuffer = malloc(sizeof(Type));
    *((Type*)(*destinationBuffer)) = getType();
    return sizeof(Type);
}

void Signal::deserialize(uint64_t length, void* bufferToUse)
    {
    signalHandler();
    }

void Signal::setValue(void* valueToSet)
    {
    //NON HA SENSO, NON C'È VALUE!
    }

void* Signal::getValue()
    {
    //NON HA SENSO, NON C'È VALUE!
    return NULL;
    }
