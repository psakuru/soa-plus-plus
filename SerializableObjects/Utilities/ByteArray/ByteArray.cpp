#include "ByteArray.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>
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

ByteArray::ByteArray(void* byteArrayToSet, uint64_t lengthToSet)
{
    byteArray = (byte*)malloc(lengthToSet*sizeof(byte));
    memcpy(byteArray, byteArrayToSet, lengthToSet);
    length = lengthToSet;

}

ByteArray::~ByteArray()
{
    free(byteArray); //PROVA! E' UN MEMORY LEAK, QUESTA E' UNA PROVA!
    byteArray = NULL;

}

byte& ByteArray::operator[](const uint64_t index)
{
    return byteArray[index];
}

void ByteArray::operator=(const ByteArray& byteArrayToCopy)
{

    /* ATTENZIONE: IL SEGUENTE BLOCCO ERA IN if(byteArray != NULL) */
    free(byteArray);
    byteArray = NULL;
    length = 0;

    /*                                                             */
    byteArray = (byte*)malloc(byteArrayToCopy.length);
    length = byteArrayToCopy.length;
    memcpy(byteArray, byteArrayToCopy.byteArray, length);
}

void ByteArray::erase()
{
    free(byteArray);
    byteArray = NULL;
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

    }
    memcpy(byteArray + length, &bufferToUse[startingPosition], fragmentLength); //TODO Attenzione, aggiunto +length, dovrebbe essere giusto
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
