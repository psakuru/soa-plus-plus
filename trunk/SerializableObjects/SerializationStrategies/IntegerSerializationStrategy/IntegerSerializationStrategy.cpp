#include "IntegerSerializationStrategy.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

IntegerSerializationStrategy::IntegerSerializationStrategy(){}

IntegerSerializationStrategy::IntegerSerializationStrategy(int32_t& userReferenceToSet)
: GenericSerializableReferenceLayer<int32_t>(userReferenceToSet){}

IntegerSerializationStrategy::IntegerSerializationStrategy(int32_t* userReferenceToSet, bool shared)
: GenericSerializableReferenceLayer<int32_t>(userReferenceToSet, shared){}

Type IntegerSerializationStrategy::getType() const
{
    return SERIALIZABLE_INTEGER;
}

int IntegerSerializationStrategy::getValueLengthLength()
{
	return sizeof(uint8_t);
}

uint64_t IntegerSerializationStrategy::serialize(void** destinationBuffer)
{
    int bufferSize = sizeof(Type) + sizeof(uint8_t) + sizeof(int32_t); // | Type | valueLength | value |
    *destinationBuffer = malloc(bufferSize); //TODO malloc exception?
    *((Type*)(*destinationBuffer)) = getType();
    *((uint8_t*)(((Type*)(*destinationBuffer))+1)) = sizeof(int32_t);
    *((int32_t*)(((uint8_t*)(((Type*)(*destinationBuffer))+1))+1)) = wrappedReference;
    return bufferSize;
}

void IntegerSerializationStrategy::deserialize(uint64_t length, void* bufferToUse) // bufferToUse:= | value |
{
    wrappedReference = *((int32_t*)(bufferToUse));
}

string IntegerSerializationStrategy::getValueTypeStringRepresentation()
{
    return "int";
}
