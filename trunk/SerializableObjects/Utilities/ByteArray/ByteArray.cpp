#include "ByteArray.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <iostream>
#include <exception>

using namespace std;

ByteArray::ByteArray()
{
    byteArray = NULL;
    length = 0;
}

ByteArray::ByteArray(const ByteArray& byteArrayToCopy)
{
    length = byteArrayToCopy.length;
    byteArray = (byte*)malloc(length*sizeof(byte));
    memcpy(byteArray, byteArrayToCopy.byteArray, length);
}

ByteArray::ByteArray(uint64_t length)
{
    byteArray = (byte*)malloc(length*sizeof(byte));
    this->length = length;
}

ByteArray::ByteArray(void* byteArrayToSet, uint64_t lengthToSet)
{
	length = lengthToSet;
    byteArray = (byte*)malloc(lengthToSet*sizeof(byte));
    memcpy(byteArray, byteArrayToSet, lengthToSet);
}

ByteArray::~ByteArray()
{
    erase();
}

byte& ByteArray::operator[](const uint64_t index)
{
    return byteArray[index];
}

void ByteArray::operator=(const ByteArray& byteArrayToCopy)
{
	erase();
    length = byteArrayToCopy.length;
    byteArray = (byte*)malloc(length*sizeof(byte));
    memcpy(byteArray, byteArrayToCopy.byteArray, length);}

void ByteArray::erase()
{
    free(byteArray);
    byteArray = NULL;
    length = 0;
}

void ByteArray::append(byte* bufferToUse, uint64_t startingPosition, uint64_t fragmentLength)
{
    byte* temporaryPointer = (byte*)realloc(byteArray, length + fragmentLength);
    if(temporaryPointer != NULL)
    {
        byteArray = temporaryPointer;
		memcpy(byteArray + length, &bufferToUse[startingPosition], fragmentLength);
		length = length + fragmentLength;
    }
	else
	{
		throw exception();
	}

}

uint64_t ByteArray::getLength()
{
    return length;
}

const byte* ByteArray::getPointer()
{
    return byteArray;
}
