#ifndef TERMINALSERIALIZABLEOBJECTBUILDER_H
#define TERMINALSERIALIZABLEOBJECTBUILDER_H

#include "../SerializableObjectBuilder.h"
#include <stdlib.h>

template <typename T>
class TerminalSerializableObjectBuilder : public SerializableObjectBuilder
{
public:
    int getValueLengthLength(Type receivedType)
    {
        T dummyT;
        return dummyT.getValueLengthLength();
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
