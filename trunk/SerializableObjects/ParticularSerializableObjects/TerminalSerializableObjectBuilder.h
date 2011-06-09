#ifndef TERMINALSERIALIZABLEOBJECTBUILDER_H
#define TERMINALSERIALIZABLEOBJECTBUILDER_H

#include "../../SerializableObjectBuiler.h"

template <typename T>
class TerminalSerializableObjectBuilder : public SerializableObjectBuiler
{
public:
    int getValueLengthLength(Type receivedType)
    {
        return T::getValueLengthLength;
    }
    SerializableObject* delegateBuilding(Type typeToBuild, uint64_t valueLength, void* value)
    {
        //TODO controllare che T sia derivato da SerializableObject
        SerializableObject* serializableObjectToReturn = new T();
        serializableObjectToReturn->deserialize(valueLength, value);
        free(value);
        return serializableObjectToReturn;
    }
};

#endif // TERMINALSERIALIZABLEOBJECTBUILDER_H
