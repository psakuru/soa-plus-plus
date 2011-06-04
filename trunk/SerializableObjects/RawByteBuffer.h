#ifndef RAWBYTEBUFFER_H
#define RAWBYTEBUFFER_H

#include "ByteArray/ByteArray.h"

class RawByteBuffer : public SerializableObject
{
    private:
        ByteArray& value;
    public:
        RawByteBuffer();
        RawByteBuffer(ByteArray& valueToSet);
        virtual ~RawByteBuffer();
        /** Default destructor */
        void operator=(const SerializableObject&);
        uint64_t serialize(void* destinationBuffer);
        void deserialize(void* bufferToUse);
};

#endif // RAWBYTEBUFFER_H
