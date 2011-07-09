#include "ImageNotFoundSerializationStrategy.h"

BadRequestSerializationStrategy::BadRequestSerializationStrategy() {}

BadRequestSerializationStrategy::BadRequestSerializationStrategy(BadRequestSignal& userReference) {} // Per uniformità con gli altri SerializableObject.

void BadRequestSerializationStrategy::signalHandler()
{
    
    throw ImageNotFoundException();
}

Type BadRequestSerializationStrategy::getSignalType() const
{
    return SIGNAL_IMAGENOTFOUND;
}

int BadRequestSerializationStrategy::getValueLengthLength()
{
    return sizeof(Type);
}
