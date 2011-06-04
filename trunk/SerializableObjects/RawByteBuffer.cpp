#include "RawByteBuffer.h"

RawByteBuffer::RawByteBuffer() : value(*(new ByteArray))
{
}

RawByteBuffer::RawByteBuffer(ByteArray& valueToSet) : value(valueToSet)
{
}

RawByteBuffer::~RawByteBuffer()
{
}

void RawByteBuffer::operator=(const SerializableObject&)
    {
    const RawByteBuffer* castReference = dynamic_cast<const RawByteBuffer*>(&objectToCopy);
    value = castReference->value;
    }

uint64_t serialize(void* destinationBuffer)
    {
    uint64_t size = sizeof(uint64_t) + value.length;
    destinationBuffer = malloc(size);
    *((uint64_t*)destinationBuffer) = value.length;
    for(int i = 0; i < value.length(); i++)
        {
        *(((byte*)destinationBuffer)+sizeof(uint64_t)+i) = value[i];
        }
    return size;
    }

void deserialize(void* bufferToUse)
{
    value.erase();
    value.append((byte*)bufferToUse,sizeof(uint64_t), *((uint64_t*)bufferToUse));
}
