#include "ByteArray.h"
#include <stdlib.h>

ByteArray::ByteArray()
{
    byteArray = NULL;
    length = 0;
}

ByteArray::ByteArray(uint64_t length)
{
    byteArray = (byte*)malloc(length*sizeof(byte));
    this->length = length;
}

ByteArray::ByteArray(void* byteArrayToSet, uint64_t lengthToSet) : byteArray((byte*)byteArrayToSet), length(lengthToSet)
{
}

ByteArray::~ByteArray()
{
    free(byteArray);
}

byte& ByteArray::operator[](const uint64_t index)
    {
    return *(byteArray + index*sizeof(byte));
    }

void ByteArray::operator=(const ByteArray& byteArrayToCopy)
    {
    free(byteArray);
    byteArray = (byte*)malloc(byteArrayToCopy.length);
    for(int i = 0; i < length; i++)
        {
        byteArray[i] = byteArrayToCopy.byteArray[i];
        }
    }

void ByteArray::erase()
{
    free(byteArray);
    byteArray = NULL;
    length = 0;
}

void ByteArray::append(byte* bufferToUse, uint64_t startingPosition, uint64_t fragmentLength)
{
    byteArray = (byte*)realloc(byteArray, length + fragmentLength);
    for(int i = 0; i < fragmentLength; i++)
        {
        byteArray[length + i] = bufferToUse[startingPosition + i];
        }
    length = length + fragmentLength;
}

uint64_t ByteArray::getLength()
{
    return length;
}

const byte* ByteArray::getPointer()
    {
    return byteArray;
    }
