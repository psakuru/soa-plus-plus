#include "String.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

String::String() : value(*(new string()))
{
}

String::String(string& valueToSet) : value(valueToSet)
{
}

String::~String()
{
}

void String::operator=(const SerializableObject& objectToCopy)
{
    const String* castReference = dynamic_cast<const String*>(&objectToCopy);
    value = castReference->value;
}

Type Integer::getType()
{
    return SERIALIZABLE_STRING;
}

int Integer::getValueLengthLength()
{
    return sizeof(size_t);
}

uint64_t String::serialize(void** destinationBuffer)
{
    uint64_t size = sizeof(Type) + sizeof(size_t) + value.length()*sizeof(char);
    *destinationBuffer = malloc(size);
    *((Type*)(*destinationBuffer)) = objectType;
    *((size_t*)(((Type*)(*destinationBuffer))++)) = value.length();
    for(int i = 0; i < value.length(); i++)
    {
        *((char*)(((byte*)(*destinationBuffer)) + sizeof(Type) + sizeof(size_t) + i)) = value.at(i);
    }
    return size;
}

void String::deserialize(uint64_t length, void* bufferToUse)
{
    value.erase();
    value.append((char*)bufferToUse, 0, length);
}
