#include "Real.h"

Real::Real()
{
    value = 0;
}

Real::Real(double valueToSet)
{
    value = valueToSet;
}

Real::~Real()
{
}

Type Real::getType()
{
    return SERIALIZABLE_REAL;
}

int Real::getValueLengthLength()
{
	return sizeof(uint8_t);
}

void Real::operator=(const SerializableObject& objectToCopy)
    {
    const Real* castReference = dynamic_cast<const Real*>(&objectToCopy);
    value = castReference->value;
    }

uint64_t Real::Real(void** destinationBuffer)
    {
    int bufferSize = sizeof(Type) + sizeof(uint8_t) + sizeof(double); // | Type | valueLength | value |
    *destinationBuffer = malloc(bufferSize);
    *((Type*)(*destinationBuffer)) = objectType;
    *((uint8_t*)(((Type*)(*destinationBuffer))++)) = sizeof(double);
    *((double*)(((uint8_t*)(((Type*)(*destinationBuffer))++))++)) = value;
    return bufferSize;
    }

void deserialize(uint64_t length, void* bufferToUse)
    {
    value = *((double*)bufferToUse);
    }
