#include "SignalSerializationStrategy.h"
#include <stdlib.h>

SignalSerializationStrategy::SignalSerializationStrategy()
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
