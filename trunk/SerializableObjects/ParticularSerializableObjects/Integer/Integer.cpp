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
    return SERIALIZABLE_INTEGER;
}

int Integer::getValueLengthLength()
{
	return sizeof(uint8_t);
}

void Integer::operator=(const SerializableObject& objectToCopy)
{
    const Integer* castReference = dynamic_cast<const Integer*>(&objectToCopy);
    value = castReference->value;
}

uint64_t Integer::serialize(void** destinationBuffer)
{
    int bufferSize = sizeof(Type) + sizeof(uint8_t) + sizeof(int32_t); // | Type | valueLength | value |
    *destinationBuffer = malloc(bufferSize);
    *((Type*)(*destinationBuffer)) = objectType;
    *((uint8_t*)(((Type*)(*destinationBuffer))++)) = sizeof(int32_t);
    *((int32_t*)(((uint8_t*)(((Type*)(*destinationBuffer))++))++)) = value;
    return bufferSize;
}

void deserialize(uint64_t length, void* bufferToUse) // bufferToUse:= | value |
{
    value = *((int32_t*)(bufferToUse));
}
