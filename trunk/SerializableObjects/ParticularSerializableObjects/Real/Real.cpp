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

Type Integer::getType()
{
    return SERIALIZABLE_REAL;
}

void Real::operator=(const SerializableObject& objectToCopy)
    {
    const Real* castReference = dynamic_cast<const Real*>(&objectToCopy);
    value = castReference->value;
    }

uint64_t Real::Real(void** destinationBuffer)
    {
    *destinationBuffer = malloc(sizeof(double));
    *((double*)(*destinationBuffer)) = value;
    return sizeof(double);
    }

void deserialize(uint64_t length, void* bufferToUse)
    {
    value = *((double*)bufferToUse);
    }
