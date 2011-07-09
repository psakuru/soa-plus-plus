#include "ImageNotFoundSerializationStrategy.h"

ImageNotFoundSerializationStrategy::ImageNotFoundSerializationStrategy() {}

ImageNotFoundSerializationStrategy::ImageNotFoundSerializationStrategy(ImageNotFoundSignal& userReference) {} // Per uniformità con gli altri SerializableObject.

void ImageNotFoundSerializationStrategy::signalHandler()
{
    
    throw ImageNotFoundException();
}

Type ImageNotFoundSerializationStrategy::getSignalType() const
{
    return SIGNAL_IMAGENOTFOUND;
}

int ImageNotFoundSerializationStrategy::getValueLengthLength()
{
    return sizeof(Type);
}
