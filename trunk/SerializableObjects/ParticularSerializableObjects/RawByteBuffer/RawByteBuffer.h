#ifndef RAWBYTEBUFFER_H
#define RAWBYTEBUFFER_H

#include "../../SerializableObject.h"
#include "../../ByteArray/ByteArray.h"
#include "../../TypeConstants.h"

class RawByteBuffer : public SerializableObject
{
    private:
        ByteArray& value;
    public:
        RawByteBuffer();
        RawByteBuffer(ByteArray& valueToSet);
        virtual ~RawByteBuffer();
        Type getType();
        int getValueLengthLength();
        void operator=(const SerializableObject&);
        uint64_t serialize(void** destinationBuffer);
        void deserialize(void* bufferToUse);
};

#endif // RAWBYTEBUFFER_H
