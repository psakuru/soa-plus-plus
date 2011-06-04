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
        ByteArray(uint64_t length);
        virtual ~ByteArray();
        byte& operator[](const uint64_t index); //Viola l' incapsulamento
};

#endif // BYTEARRAY_H
