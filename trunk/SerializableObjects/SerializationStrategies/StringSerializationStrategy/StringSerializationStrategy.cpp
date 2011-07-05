#include "StringSerializationStrategy.h"
#include <stdlib.h>

StringSerializationStrategy::StringSerializationStrategy(string& userReferenceToSet)
    : GenericSerializableReferenceLayer<string>(userReferenceToSet) {}

StringSerializationStrategy::StringSerializationStrategy(string* userReferenceToSet, bool shared)
    : GenericSerializableReferenceLayer<string>(userReferenceToSet, shared) {}

Type StringSerializationStrategy::getType() const
{
    return SERIALIZABLE_STRING;
}

int StringSerializationStrategy::getValueLengthLength()
{
    return sizeof(uint64_t);
}

uint64_t StringSerializationStrategy::serialize(void** destinationBuffer)
{
    uint64_t size = sizeof(Type) + sizeof(uint64_t) + wrappedReference.length()*sizeof(char);
    *destinationBuffer = malloc(size);
    *((Type*)(*destinationBuffer)) = getType();
    *((uint64_t*)(((Type*)(*destinationBuffer))+1)) = wrappedReference.length();
    for(unsigned int i = 0; i < wrappedReference.length(); i++)
    {
        *((char*)(((uint8_t*)(*destinationBuffer)) + sizeof(Type) + sizeof(uint64_t) + i)) = wrappedReference.at(i);
    }
    return size;
}

void StringSerializationStrategy::deserialize(uint64_t length, void* bufferToUse)
{
    wrappedReference.erase();
    wrappedReference.append((char*)bufferToUse, length);
}

string StringSerializationStrategy::getValueTypeStringRepresentation()
{
    return "string";
}
