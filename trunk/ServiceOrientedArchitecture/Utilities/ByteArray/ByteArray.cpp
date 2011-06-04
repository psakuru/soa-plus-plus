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
