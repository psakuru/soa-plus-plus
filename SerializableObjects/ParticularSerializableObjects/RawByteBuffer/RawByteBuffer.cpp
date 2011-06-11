#include "RawByteBuffer.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

RawByteBuffer::RawByteBuffer() : value(*(new ByteArray(1)))
{
    userReference = false;
}

RawByteBuffer::RawByteBuffer(ByteArray& valueToSet) : value(valueToSet)
{
    userReference = true;
}

RawByteBuffer::~RawByteBuffer()
{
    if(!userReference) delete &value;
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
    cout << "Operatore di assegnamento di RawByteBuffer " << endl;
    const RawByteBuffer* castReference = dynamic_cast<const RawByteBuffer*>(&objectToCopy);
    value = castReference->value;
}

uint64_t RawByteBuffer::serialize(void** destinationBuffer)
{
    uint64_t bufferSize = sizeof(Type) + sizeof(uint64_t) + value.getLength();
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
    ) = value.getLength();
    for(int i = 0; i < value.getLength(); i++)
    {
        *(((byte*)(*destinationBuffer))+sizeof(Type) + sizeof(uint64_t)+i) = value[i];
    }
    return bufferSize;
}

void RawByteBuffer::deserialize(uint64_t length, void* bufferToUse)
{
    cout << "deserializa di RawByteBuffer" << endl;
    value.erase();
    value.append((byte*)bufferToUse, 0, length);
}

void RawByteBuffer::setValue(void* valueToSet)
{
    value = *((ByteArray*)(valueToSet)); //Attivato l' operatore=, avviene una copia dei valori passati
}

void* RawByteBuffer::getValue()
{
    return new ByteArray(value); //Ritornato un oggetto nuovo, non viene rotto l' incapsulamento
}
