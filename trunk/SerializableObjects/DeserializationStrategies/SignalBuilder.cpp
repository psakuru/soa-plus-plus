#include "SignalBuilder.h"
#include "../SerializationStrategies/SignalSerializationStrategy/SignalTypeConstants.h"
#include <cstddef>

SignalBuilder::SignalBuilder()
{
    //ctor
}

SignalBuilder::~SignalBuilder()
{
    //dtor
}

SerializableObject* SignalBuilder::delegateBuilding(Type typeToBuild, uint64_t valueLength, void* value)
{
    Type signalType = *((Type*)value);
    subSerializableObjectBuilders[signalType]->delegateBuilding(signalType, 0, NULL);
}
