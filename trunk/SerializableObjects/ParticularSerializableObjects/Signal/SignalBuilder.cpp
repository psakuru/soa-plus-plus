#include "SignalBuilder.h"
#include "SignalTypeConstants.h"

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
    subSerializableObjectBuilders[signalType].delegateBuilding(signalType, 0, NULL);
}
