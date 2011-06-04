#include "ByteArray.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>
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

ByteArray::ByteArray(void* byteArrayToSet, uint64_t lengthToSet) : byteArray((byte*)byteArrayToSet), length(lengthToSet)
{
}

ByteArray::~ByteArray()
{
    cout << hex <<  (unsigned int)byteArray << endl;
    free(byteArray);
    byteArray = NULL;
}

byte& ByteArray::operator[](const uint64_t index)
    {
    return *(byteArray + index*sizeof(byte));
    }

void ByteArray::operator=(const ByteArray& byteArrayToCopy)
    {
    if(byteArray != NULL)
        {
        free(byteArray);
        byteArray = NULL;
        }
    byteArray = (byte*)malloc(byteArrayToCopy.length);
    for(int i = 0; i < length; i++)
        {
        byteArray[i] = byteArrayToCopy.byteArray[i];
        }
    }

void ByteArray::erase()
{
    if(byteArray != NULL)
        {
        free(byteArray);
        byteArray = NULL;
        }
    length = 0;
}

void ByteArray::append(byte* bufferToUse, uint64_t startingPosition, uint64_t fragmentLength)
{
    byte* temporatyPointer = (byte*)realloc(byteArray, length + fragmentLength);
    if(temporatyPointer != NULL)
        {
        byteArray = temporatyPointer;
        }
    else
        {
        cout << "MEMORY LEAK!!!!" << endl;
        }
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
