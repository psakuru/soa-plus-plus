#include "SerializableObjectBuilder.h"

SerializableObjectBuilder::SerializableObjectBuilder()
{
    //ctor
}

SerializableObjectBuilder::~SerializableObjectBuilder()
{
    //dtor
}

void SerializableObjectBuilder::addSerializableObjectBuilder(Type builtType, SerializableObjectBuilder* builderToAdd)
{
    subSerializableObjectBuilders[builtType] = builderToAdd;
}

void SerializableObjectBuilder::removeSerializableObjectBuilder(Type builtType)
{
    subSerializableObjectBuilders.erase(builtType);
}

int SerializableObjectBuilder::getValueLengthLength(receivedType)
{
    return subSerializableObjectBuilders[receivedType].getValueLengthLength(receivedType);
}

SerializableObject* SerializableObjectBuilder::delegateBuilding(Type typeToBuild, uint64_t valueLength, void* value)
{
    return subSerializableObjectBuilders[typeToBuild].delegateBuilding(typeToBuild, valueLength, value);
}
