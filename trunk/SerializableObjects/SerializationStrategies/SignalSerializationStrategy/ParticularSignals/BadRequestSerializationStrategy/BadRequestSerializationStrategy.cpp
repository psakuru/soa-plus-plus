#include "BadRequestSerializationStrategy.h"
#include <exception>
#include <iostream>
using namespace std;

BadRequestSerializationStrategy::BadRequestSerializationStrategy() {}

BadRequestSerializationStrategy::BadRequestSerializationStrategy(BadRequestSignal& userReference) {} // Per uniformità con gli altri SerializableObject.

void BadRequestSerializationStrategy::signalHandler()
{
    /* Corpo del signal handler */
}

Type BadRequestSerializationStrategy::getSignalType() const
{
    return SIGNAL_BAD_REQUEST;
}

int BadRequestSerializationStrategy::getValueLengthLength()
{
    return sizeof(Type);
}
