#ifndef RAWBYTEBUFFER_H
#define RAWBYTEBUFFER_H

#include "../../SerializableObject.h"
#include "../../Utilities/ByteArray/ByteArray.h"
#include "../../TypeConstants.h"

class RawByteBuffer : public SerializableObject
{   public: //RIMETTI value private!
        ByteArray& value;

        RawByteBuffer();
        RawByteBuffer(ByteArray& valueToSet);
        virtual ~RawByteBuffer();
        Type getType();
        int getValueLengthLength();
        void operator=(const SerializableObject&);
        uint64_t serialize(void** destinationBuffer);
        void deserialize(uint64_t length, void* bufferToUse);
};

#endif // RAWBYTEBUFFER_H
