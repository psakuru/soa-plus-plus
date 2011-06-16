#include "RealSerializationStrategy.h"
#include <stdlib.h>

RealSerializationStrategy::RealSerializationStrategy(){}

RealSerializationStrategy::RealSerializationStrategy(double& userReferenceToSet)
: GenericSerializableReferenceLayer<double>(userReferenceToSet){}

RealSerializationStrategy::RealSerializationStrategy(double* userReferenceToSet, bool shared)
: GenericSerializableReferenceLayer<double>(userReferenceToSet, shared){}

Type RealSerializationStrategy::getType()
{
    return SERIALIZABLE_REAL;
}

int RealSerializationStrategy::getValueLengthLength()
{
	return sizeof(uint8_t);
}

uint64_t RealSerializationStrategy::serialize(void** destinationBuffer)
    {
    int bufferSize = sizeof(Type) + sizeof(uint8_t) + sizeof(double); // | Type | valueLength | value |
    *destinationBuffer = malloc(bufferSize);
    *((Type*)(*destinationBuffer)) = getType();
    *((uint8_t*)(((Type*)(*destinationBuffer))+1)) = sizeof(double);
    *((double*)(((uint8_t*)(((Type*)(*destinationBuffer))+1))+1)) = wrappedReference;
    return bufferSize;
    }

void RealSerializationStrategy::deserialize(uint64_t length, void* bufferToUse)
    {
    wrappedReference = *((double*)bufferToUse);
    }
