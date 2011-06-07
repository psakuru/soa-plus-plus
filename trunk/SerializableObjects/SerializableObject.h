#ifndef SERIALIZABLEOBJECT_H
#define SERIALIZABLEOBJECT_H

#include <stdint.h>
#include "TypeConstants.h"

typedef int Type;

class SerializableObject
{
    public:
        static const Type objectType = SERIALIZABLE_OBJECT;
        virtual ~SerializableObject();
        virtual void operator=(const SerializableObject&) = 0;
        virtual uint64_t serialize(void** destinationBuffer) = 0;
        virtual void deserialize(void* bufferToUse) = 0;
};

#endif // SERIALIZABLEOBJECT_H
