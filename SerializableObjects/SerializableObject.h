#ifndef SERIALIZABLEOBJECT_H
#define SERIALIZABLEOBJECT_H

#include <stdint.h>
#include "TypeConstants.h"
#include <string>
using namespace std;

class SerializableObject
{
public:
    virtual ~SerializableObject() = 0;
    virtual void operator=(const SerializableObject&) = 0;
    virtual int getValueLengthLength() = 0;
    virtual Type getType() const = 0;
    virtual uint64_t serialize(void** destinationBuffer) = 0;
    virtual void deserialize(uint64_t length, void* bufferToUse) = 0;
    virtual void setValue(void* valueToSet) = 0;
    virtual void* getValue() = 0;
    virtual string getValueTypeStringRepresentation() = 0;
};

#endif // SERIALIZABLEOBJECT_H
