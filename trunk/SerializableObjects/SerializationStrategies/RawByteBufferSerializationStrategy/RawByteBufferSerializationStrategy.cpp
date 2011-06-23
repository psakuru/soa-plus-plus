// Include il ReferenceSerializationLayer
#include "RawByteBufferSerializationStrategy.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

RawByteBufferSerializationStrategy::RawByteBufferSerializationStrategy(){}

RawByteBufferSerializationStrategy::RawByteBufferSerializationStrategy(ByteArray& userReferenceToSet)
: GenericSerializableReferenceLayer<ByteArray>(userReferenceToSet){}

RawByteBufferSerializationStrategy::RawByteBufferSerializationStrategy(ByteArray* userReferenceToSet, bool shared)
: GenericSerializableReferenceLayer<ByteArray>(userReferenceToSet, shared){}

Type RawByteBufferSerializationStrategy::getType() const
{
    return SERIALIZABLE_RAW_BYTE_BUFFER;
}

int RawByteBufferSerializationStrategy::getValueLengthLength()
{
    return sizeof(uint64_t);
}

uint64_t RawByteBufferSerializationStrategy::serialize(void** destinationBuffer)
{
    uint64_t bufferSize = sizeof(Type) + sizeof(uint64_t) + wrappedReference.getLength();
    *destinationBuffer = malloc(bufferSize);
    *((Type*)(*destinationBuffer)) = getType();
    *(
        (uint64_t*)
        (
            (
                (Type*)
                (
                    *destinationBuffer
                )
            )+1
        )
    ) = wrappedReference.getLength();
    //cout << "Serializzazione di RawByteBuffer: ho scritto " << wrappedReference.getLength() << " nel campo length" << endl;
    for(unsigned int i = 0; i < wrappedReference.getLength(); i++)
    {
        *(((byte*)(*destinationBuffer))+sizeof(Type) + sizeof(uint64_t)+i) = wrappedReference[i];
    }
    return bufferSize;
}

void RawByteBufferSerializationStrategy::deserialize(uint64_t length, void* bufferToUse)
{
    wrappedReference.erase();
    wrappedReference.append((byte*)bufferToUse, 0, length);
}

string RawByteBufferSerializationStrategy::getValueTypeStringRepresentation()
{
    return "ByteArray";
}
