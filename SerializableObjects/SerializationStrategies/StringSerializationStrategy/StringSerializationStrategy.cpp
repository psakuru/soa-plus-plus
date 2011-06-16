#include "StringSerializationStrategy.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

StringSerializationStrategy::StringSerializationStrategy(){}

StringSerializationStrategy::StringSerializationStrategy(string& userReferenceToSet)
: GenericSerializableReferenceLayer<string>(userReferenceToSet){}

Type StringSerializationStrategy::getType()
{
    return SERIALIZABLE_STRING;
}

StringSerializationStrategy::StringSerializationStrategy(string* userReferenceToSet, bool shared)
: GenericSerializableReferenceLayer<string>(userReferenceToSet, shared){}

int StringSerializationStrategy::getValueLengthLength()
{
    return sizeof(size_t);
}

uint64_t StringSerializationStrategy::serialize(void** destinationBuffer)
{
    uint64_t size = sizeof(Type) + sizeof(size_t) + wrappedReference.length()*sizeof(char);
    *destinationBuffer = malloc(size);
    *((Type*)(*destinationBuffer)) = getType();
    *((size_t*)(((Type*)(*destinationBuffer))+1)) = wrappedReference.length();
    for(unsigned int i = 0; i < wrappedReference.length(); i++)
    {
        *((char*)(((uint8_t*)(*destinationBuffer)) + sizeof(Type) + sizeof(size_t) + i)) = wrappedReference.at(i);
    }
    return size;
}

void StringSerializationStrategy::deserialize(uint64_t length, void* bufferToUse)
{
    wrappedReference.erase();
    wrappedReference.append((char*)bufferToUse, length);
}
