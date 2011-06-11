#include "Integer.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

Integer::Integer() : value(*(new int))
{
userReference = false;
}

Integer::Integer(int32_t& valueToSet) : value(valueToSet)
{
userReference = true;
}

Integer::~Integer()
{
if(!userReference) delete &value;
}

Type Integer::getType()
{
    return SERIALIZABLE_INTEGER;
}

int Integer::getValueLengthLength()
{
	return sizeof(uint8_t);
}

void Integer::operator=(const SerializableObject& objectToCopy)
{
    const Integer* castReference = dynamic_cast<const Integer*>(&objectToCopy);
    value = castReference->value;
}

uint64_t Integer::serialize(void** destinationBuffer)
{
    int bufferSize = sizeof(Type) + sizeof(uint8_t) + sizeof(int32_t); // | Type | valueLength | value |
    *destinationBuffer = malloc(bufferSize);
    *((Type*)(*destinationBuffer)) = getType();
    *((uint8_t*)(((Type*)(*destinationBuffer))+1)) = sizeof(int32_t);
    *((int32_t*)(((uint8_t*)(((Type*)(*destinationBuffer))+1))+1)) = value;
    return bufferSize;
}

void Integer::deserialize(uint64_t length, void* bufferToUse) // bufferToUse:= | value |
{
    value = *((int32_t*)(bufferToUse));
    cout << "Il valore dell' Integer ricevuto è " << value << endl;
}

void Integer::setValue(void* valueToSet)
    {
    value = *((int32_t*)(valueToSet));
    }

void* Integer::getValue()
    {
    return new int(value);
    }
