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

ByteArray::ByteArray(void* byteArrayToSet, uint64_t lengthToSet) //byteArrayToSet deve essere stato fatto con la malloc!
{
    byteArray = (byte*)byteArrayToSet;
    length = lengthToSet;
}

ByteArray::~ByteArray()
{
    free(byteArray);
    byteArray = NULL;
    cout << "Memoria del ByteArray correttamente rilasciata" << endl;
}

byte& ByteArray::operator[](const uint64_t index)
    {
    return byteArray[index];
    }

void ByteArray::operator=(const ByteArray& byteArrayToCopy)
    {
    cout << "Operatore di assegnamento di ByteArray" << endl;
    if(byteArray != NULL)
        {
        free(byteArray);
        byteArray = NULL;
        length = 0;
        cout << "Libero la memoria del ByteArray destinatario della copia" << endl;
        }
    byteArray = (byte*)malloc(byteArrayToCopy.length);
    length = byteArrayToCopy.length;
    memcpy(byteArray, byteArrayToCopy.byteArray, length);
    }

void ByteArray::erase()
{
    if(byteArray != NULL)
        {
        cout << "ByteArray::erase()" <<  endl;
        free(byteArray);
        cout << "\t free eseguita" <<  endl;
        strerror(errno);
        byteArray = NULL;
        }
    length = 0;
}

void ByteArray::append(byte* bufferToUse, uint64_t startingPosition, uint64_t fragmentLength)
{
    byte* temporatyPointer = (byte*)realloc(byteArray, length + fragmentLength);
    cout << "ByteArray::append()" <<  endl;
    if(temporatyPointer != NULL)
        {
        byteArray = temporatyPointer;
        }
    else
        {
        cout << "MEMORY LEAK!!!!" << endl;
        }
    memcpy(byteArray, &bufferToUse[startingPosition], fragmentLength);
    length = length + fragmentLength;
    cout << "La lunghezza del buffer dopo la append è: " << length << endl;
}

uint64_t ByteArray::getLength()
{
    return length;
}

const byte* ByteArray::getPointer()
    {
    return byteArray;
    }
