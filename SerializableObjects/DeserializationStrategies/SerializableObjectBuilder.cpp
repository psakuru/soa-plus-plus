#include "SerializableObjectBuilder.h"
#include "Exceptions/UnknownType.h"

SerializableObjectBuilder::~SerializableObjectBuilder()
{
    map<Type, SerializableObjectBuilder*>::iterator i = subSerializableObjectBuilders.begin();
    for(; i != subSerializableObjectBuilders.end(); i++)
    {
        delete (*i).second;
    }
}

bool SerializableObjectBuilder::checkType(Type typeToCheck)
{
    if(subSerializableObjectBuilders.find(typeToCheck) != subSerializableObjectBuilders.end())
    {
        return true;
    }
    return false;
}

SerializableObjectBuilder* SerializableObjectBuilder::operator[](Type builtType)
{
    if(checkType(builtType))
    {
        return subSerializableObjectBuilders[builtType];
    }
    throw UnknownType();
    return NULL;
}

void SerializableObjectBuilder::addSerializableObjectBuilder(Type builtType, SerializableObjectBuilder* builderToAdd)
{
	if(subSerializableObjectBuilders.empty() || (subSerializableObjectBuilders.find(builtType) == subSerializableObjectBuilders.end()))
    {
        subSerializableObjectBuilders[builtType] = builderToAdd;
	}
}

void SerializableObjectBuilder::removeSerializableObjectBuilder(Type builtType)
{
    if(checkType(builtType))
    {
        delete subSerializableObjectBuilders[builtType];
        subSerializableObjectBuilders.erase(builtType);
    }
}

int SerializableObjectBuilder::getValueLengthLength(Type receivedType)
{
    if(checkType(receivedType))
    {
        return subSerializableObjectBuilders[receivedType]->getValueLengthLength(receivedType); // Richiedo ad uno dei nodi a livello inferiore la lunghezza della lunghezza.
    }
    throw UnknownType();
    return 0;
}

SerializableObject* SerializableObjectBuilder::delegateBuilding(Type typeToBuild, uint64_t valueLength, void* value)
{
    if(checkType(typeToBuild))
    {
        return subSerializableObjectBuilders[typeToBuild]->delegateBuilding(typeToBuild, valueLength, value); // Richiedo ad uno dei nodi a livello inferiore di costruire il serializable object.
    }
    throw UnknownType();
    return NULL;
}
