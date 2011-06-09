#ifndef SERIALIZABLEOBJECT_H
#define SERIALIZABLEOBJECT_H

#include <stdint.h>
#include "TypeConstants.h"

class SerializableObject
{
    public:
        SerializableObject();
        virtual ~SerializableObject();
        virtual void operator=(const SerializableObject&) = 0;
        virtual int getValueLengthLength() = 0;
        virtual Type getType() = 0;
        virtual uint64_t serialize(void** destinationBuffer) = 0;
        virtual void deserialize(uint64_t length, void* bufferToUse) = 0;
};

#endif // SERIALIZABLEOBJECT_H
