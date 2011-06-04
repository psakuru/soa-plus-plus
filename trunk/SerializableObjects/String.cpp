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

uint64_t String::serialize(void* destinationBuffer)
    {
    uint64_t size = sizeof(size_t)+value.length()*sizeof(char);
    destinationBuffer = malloc(size);
    *((size_t*)destinationBuffer) = value.length();
    for(int i = 0; i < value.length(); i++)
        {
        *(((char*)destinationBuffer)+sizeof(size_t)+i) = value.at(i);
        }
    return size;
    }

void String::deserialize(void* bufferToUse)
    {
    value.erase();
    value.append((char*)bufferToUse,sizeof(size_t), *((size_t*)bufferToUse));
    }
