#include "BadRequestSerializationStrategy.h"
#include <exception>

BadRequestSerializationStrategy::BadRequestSerializationStrategy() {}

BadRequestSerializationStrategy::BadRequestSerializationStrategy(BadRequestSignal& userReference) {} // Per uniformità con gli altri SerializableObject.

void BadRequestSerializationStrategy::signalHandler()
{
    throw exception;
}

Type BadRequestSerializationStrategy::getSignalType() const
{
    return SIGNAL_BAD_REQUEST;
}

int BadRequestSerializationStrategy::getValueLengthLength()
{
    return sizeof(Type);
}
