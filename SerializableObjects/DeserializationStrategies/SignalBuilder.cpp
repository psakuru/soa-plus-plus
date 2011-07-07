#include "SignalBuilder.h"
#include "../SerializationStrategies/SignalSerializationStrategy/SignalTypeConstants.h"
#include "Exceptions/UnknownType.h"
#include <stdlib.h>
#include <cstddef>

SignalBuilder::SignalBuilder() {}

SignalBuilder::~SignalBuilder() {}

int SignalBuilder::getValueLengthLength(Type receivedType)
{
    return sizeof(uint8_t);
}

SerializableObject* SignalBuilder::delegateBuilding(Type typeToBuild, uint64_t valueLength, void* value)
{
    Type signalType = *((Type*)value);
    free(value);
    if(checkType(typeToBuild))
    {
        return subSerializableObjectBuilders[signalType]->delegateBuilding(signalType, 0, NULL);
    }
    throw UnknownType();
    return NULL;
}
