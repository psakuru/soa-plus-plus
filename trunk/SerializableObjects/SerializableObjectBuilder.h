#ifndef SERIALIZABLEOBJECTBUILDER_H
#define SERIALIZABLEOBJECTBUILDER_H

#include "TypeConstants.h"

class SerializableObjectBuilder
    {
    protected:
        map< Type, SerializableObject* > subSerializableObjectBuilders;
    public:
        virtual ~SerializableObjectBuilder();
        virtual SerializableObjectBuilder* operator[](Type builtType);
        virtual void addSerializableObjectBuilder(Type builtType, SerializableObjectBuilder* builderToAdd);
        virtual void removeSerializableObjectBuilder(Type builtType);
        virtual int getValueLengthLength(receivedType);
        virtual SerializableObject* delegateBuilding(Type typeToBuild, uint64_t valueLength, void* value);
    };


#endif // SERIALIZABLEOBJECTBUILDER_H
