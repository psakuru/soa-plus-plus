#include "SerializableObjectBuilder.h"
#include <iostream>
using namespace std;

SerializableObjectBuilder::~SerializableObjectBuilder()
{
    //dtor
}

SerializableObjectBuilder* SerializableObjectBuilder::operator[](Type builtType)
{
    return subSerializableObjectBuilders[builtType];
}

void SerializableObjectBuilder::addSerializableObjectBuilder(Type builtType, SerializableObjectBuilder* builderToAdd)
{
    subSerializableObjectBuilders[builtType] = builderToAdd;
}

void SerializableObjectBuilder::removeSerializableObjectBuilder(Type builtType)
{
    subSerializableObjectBuilders.erase(builtType);
}

int SerializableObjectBuilder::getValueLengthLength(Type receivedType)
{
    cout << "SerializableObjectBuilder: getValueLengthLength" << endl;
    return subSerializableObjectBuilders[receivedType]->getValueLengthLength(receivedType);
}

SerializableObject* SerializableObjectBuilder::delegateBuilding(Type typeToBuild, uint64_t valueLength, void* value)
{
    cout << "Verrà delegata la costruzione dell' oggetto con Type: " << typeToBuild << " valueLength: " << valueLength << endl;
    return subSerializableObjectBuilders[typeToBuild]->delegateBuilding(typeToBuild, valueLength, value);
}
