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

Type Integer::getType()
{
    return objectType;
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

void RawByteBuffer::deserialize(void* bufferToUse)
{
    cout << "Il buffer da appendere è lungo " << *((uint64_t*)bufferToUse) << " bytes" << endl;
    value.erase();
    value.append((byte*)bufferToUse, sizeof(Type) + sizeof(uint64_t), *((uint64_t*)(((Type*)(bufferToUse))++)));
}
