#ifndef BYTEARRAY_H
#define BYTEARRAY_H

#include <stdint.h>

typedef uint8_t byte;

class ByteArray
{
private:
    byte* byteArray;
    uint64_t length;
public:
    ByteArray();
    ByteArray(const ByteArray& byteArrayToCopy);
    ByteArray(uint64_t length);
    ByteArray(void* byteArrayToSet, uint64_t lengthToSet);
    virtual ~ByteArray();
    byte& operator[](const uint64_t index); //Viola l' incapsulamento
    void operator=(const ByteArray& byteArrayToCopy);
    void erase();
    void append(byte* bufferToUse, uint64_t startingPosition, uint64_t fragmentLength);
    uint64_t getLength();
    const byte* getPointer();
};

#endif // BYTEARRAY_H
