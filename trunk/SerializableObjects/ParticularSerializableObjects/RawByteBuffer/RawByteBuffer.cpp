#include "RawByteBuffer.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

RawByteBuffer::RawByteBuffer() : value(*(new ByteArray))
{
}

RawByteBuffer::RawByteBuffer(ByteArray& valueToSet) : value(valueToSet)
{
}

RawByteBuffer::~RawByteBuffer()
{
}

Type RawByteBuffer::getType()
{
    return SERIALIZABLE_RAW_BYTE_BUFFER;
}

int RawByteBuffer::getValueLengthLength()
{
	return sizeof(uint64_t);
}

void RawByteBuffer::operator=(const SerializableObject& objectToCopy)
    {
    const RawByteBuffer* castReference = dynamic_cast<const RawByteBuffer*>(&objectToCopy);
    value = castReference->value;
    }

uint64_t RawByteBuffer::serialize(void** destinationBuffer)
    {
    uint64_t bufferSize = sizeof(Type) + sizeof(uint64_t) + value.getLength();
    *destinationBuffer = malloc(bufferSize);
    *((Type*)(*destinationBuffer)) = objectType;
    *((uint64_t*)(((Type*)(*destinationBuffer))++)) = value.getLength();
    for(int i = 0; i < value.getLength(); i++)
        {
        *(((byte*)(*destinationBuffer))+sizeof(Type) + sizeof(uint64_t)+i) = value[i];
        }
    return size;
    }

void RawByteBuffer::deserialize(uint64_t length, void* bufferToUse)
{
    value.erase();
    value.append((byte*)bufferToUse, 0, length);
}
