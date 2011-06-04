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

void Integer::operator=(const SerializableObject& objectToCopy)
    {
    const Integer* castReference = dynamic_cast<const Integer*>(&objectToCopy);
    value = castReference->value;
    }

uint64_t Integer::serialize((void*)& destinationBuffer)
    {
    destinationBuffer = malloc(sizeof(int32_t));
    *((int32_t*)destinationBuffer) = value;
    return sizeof(int32_t);
    }

void deserialize(void* bufferToUse)
    {
    value = *((int32_t*)bufferToUse);
    }
