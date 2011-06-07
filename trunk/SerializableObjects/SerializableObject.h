#ifndef SERIALIZABLEOBJECT_H
#define SERIALIZABLEOBJECT_H

#include <stdint.h>
#include "TypeConstants.h"

typedef int Type;

class SerializableObject
{
    private:
        static const Type objectType = SERIALIZABLE_OBJECT;
    public:
        virtual ~SerializableObject();
        virtual void operator=(const SerializableObject&) = 0;
        virtual Type getType() = 0;
        virtual uint64_t serialize(void** destinationBuffer) = 0;
        virtual void deserialize(void* bufferToUse) = 0;
};

#endif // SERIALIZABLEOBJECT_H
