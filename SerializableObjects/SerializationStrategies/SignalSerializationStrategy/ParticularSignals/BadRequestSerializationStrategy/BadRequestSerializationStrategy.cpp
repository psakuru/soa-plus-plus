#include "BadRequestSerializationStrategy.h"
#include <exception>

BadRequestSerializationStrategy::BadRequestSerializationStrategy() {}

BadRequestSerializationStrategy::BadRequestSerializationStrategy(BadRequestSignal& userReference) {} // Per uniformità con gli altri SerializableObject.

void BadRequestSerializationStrategy::signalHandler()
{
    throw exception(); //TODO fare una eccezione a modo!
}

Type BadRequestSerializationStrategy::getSignalType() const
{
    return SIGNAL_BAD_REQUEST;
}

int BadRequestSerializationStrategy::getValueLengthLength()
{
    return sizeof(Type);
}
