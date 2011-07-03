#include "SerializableObjectBuilder.h"
#include "Exceptions/UnknownType.h"
#include <iostream>
using namespace std;

SerializableObjectBuilder::~SerializableObjectBuilder()
{
    map<Type, SerializableObjectBuilder*>::iterator i = subSerializableObjectBuilders.begin();
    for(; i != subSerializableObjectBuilders.end(); i++)
    {
        delete (*i).second;
    }
}

SerializableObjectBuilder* SerializableObjectBuilder::operator[](Type builtType)
{
    if(subSerializableObjectBuilders.find(builtType) != subSerializableObjectBuilders.end())
    {
        return subSerializableObjectBuilders[builtType];
    }
    else
    {
        throw UnknownType();
        return NULL;
    }
}

void SerializableObjectBuilder::addSerializableObjectBuilder(Type builtType, SerializableObjectBuilder* builderToAdd)
{
    subSerializableObjectBuilders[builtType] = builderToAdd;
}

void SerializableObjectBuilder::removeSerializableObjectBuilder(Type builtType)
{
    delete subSerializableObjectBuilders[builtType];
    subSerializableObjectBuilders.erase(builtType);
}

int SerializableObjectBuilder::getValueLengthLength(Type receivedType)
{
    return subSerializableObjectBuilders[receivedType]->getValueLengthLength(receivedType);
}

SerializableObject* SerializableObjectBuilder::delegateBuilding(Type typeToBuild, uint64_t valueLength, void* value)
{
    return subSerializableObjectBuilders[typeToBuild]->delegateBuilding(typeToBuild, valueLength, value);
}
