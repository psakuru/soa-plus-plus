#include "GenericSignalSerializationStrategy.h"
#include <exception>
#include <iostream>
using namespace std;

GenericSignalSerializationStrategy::GenericSignalSerializationStrategy() {}

GenericSignalSerializationStrategy::GenericSignalSerializationStrategy(GenericSignalValue& userReference) {} // Per uniformità con gli altri SerializableObject.

void GenericSignalSerializationStrategy::signalHandler() {}

Type GenericSignalSerializationStrategy::getSignalType() const
{
    return SIGNAL_GENERIC;
}

int GenericSignalSerializationStrategy::getValueLengthLength()
{
    return sizeof(Type);
}
