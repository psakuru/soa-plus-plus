#include "Integer.h"

Integer::Integer()
{
    value = 0;
}

Integer::Integer(int32_t& valueToSet)
{
    value = valueToSet;
}

Integer::~Integer()
{
}

Type Integer::getType()
{
    return objectType;
}

void Integer::operator=(const SerializableObject& objectToCopy)
{
    const Integer* castReference = dynamic_cast<const Integer*>(&objectToCopy);
    value = castReference->value;
}

uint64_t Integer::serialize(void** destinationBuffer)
{
    int bufferSize = sizeof(Type) + sizeof(int32_t); // | Type | value |
    *destinationBuffer = malloc(bufferSize);
    *((Type*)(*destinationBuffer)) = objectType;
    *((int32_t*)(((Type*)(*destinationBuffer))++)) = value;
    return bufferSize;
}

void deserialize(void* bufferToUse) // bufferToUse:= | value |
{
    value = *((int32_t*)(bufferToUse));
}
