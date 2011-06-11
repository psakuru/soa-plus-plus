#include "Real.h"
#include <stdlib.h>

Real::Real() : value(*(new double))
{
userReference = false;
}

Real::Real(double& valueToSet) : value(valueToSet)
{
userReference = true;
}

Real::~Real()
{
if(!userReference) delete &value;
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

uint64_t Real::serialize(void** destinationBuffer)
    {
    int bufferSize = sizeof(Type) + sizeof(uint8_t) + sizeof(double); // | Type | valueLength | value |
    *destinationBuffer = malloc(bufferSize);
    *((Type*)(*destinationBuffer)) = getType();
    *((uint8_t*)(((Type*)(*destinationBuffer))+1)) = sizeof(double);
    *((double*)(((uint8_t*)(((Type*)(*destinationBuffer))+1))+1)) = value;
    return bufferSize;
    }

void Real::deserialize(uint64_t length, void* bufferToUse)
    {
    value = *((double*)bufferToUse);
    }

//setValue e getValue sono STRAREPLICATE. Bisogna trovare una soluzione template o simili
void Real::setValue(void* valueToSet)
    {
    value = *((double*)(valueToSet));
    }

void* Real::getValue()
    {
    return new double(value);
    }
