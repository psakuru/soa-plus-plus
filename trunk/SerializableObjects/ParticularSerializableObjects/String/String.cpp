#include "String.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

String::String() : value(*(new string()))
{
userReference = false;
}

String::String(string& valueToSet) : value(valueToSet)
{
userReference = true;
}

String::~String()
{
if(!userReference) delete &value;
}

void String::operator=(const SerializableObject& objectToCopy)
{
    const String* castReference = dynamic_cast<const String*>(&objectToCopy);
    value = castReference->value;
}

Type String::getType()
{
    return SERIALIZABLE_STRING;
}

int String::getValueLengthLength()
{
    return sizeof(size_t);
}

uint64_t String::serialize(void** destinationBuffer)
{
    uint64_t size = sizeof(Type) + sizeof(size_t) + value.length()*sizeof(char);
    *destinationBuffer = malloc(size);
    *((Type*)(*destinationBuffer)) = getType();
    *((size_t*)(((Type*)(*destinationBuffer))+1)) = value.length();
    for(int i = 0; i < value.length(); i++)
    {
        *((char*)(((uint8_t*)(*destinationBuffer)) + sizeof(Type) + sizeof(size_t) + i)) = value.at(i);
    }
    return size;
}

void String::deserialize(uint64_t length, void* bufferToUse)
{
    value.erase();
    value.append((char*)bufferToUse, 0, length);
}

void String::setValue(void* valueToSet)
    {
    value = *((string*)(valueToSet));
    }

void* String::getValue()
    {
    return new string(value);
    }
