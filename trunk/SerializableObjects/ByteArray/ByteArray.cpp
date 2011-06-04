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

void append(byte* bufferToUse, uint64_t startingPosition, uint64_t fragmentLength)
{
    realloc(byteArry, length + fragmentLength);
    for(int i = 0; i < fragmentLength; i++)
        {
        byteArray[length + i] = bufferToUse.byteArray[startingPosition + i];
        }
    length = length + fragmentLength;
}
