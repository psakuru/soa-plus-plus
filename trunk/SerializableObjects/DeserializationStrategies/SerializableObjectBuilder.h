#ifndef SERIALIZABLEOBJECTBUILDER_H
#define SERIALIZABLEOBJECTBUILDER_H

#include <map>
#include "../SerializableObject.h"
#include "../TypeConstants.h"
using namespace std;

class SerializableObjectBuilder
    {
    protected:
        map< Type, SerializableObjectBuilder* > subSerializableObjectBuilders;
    public:
        virtual ~SerializableObjectBuilder();
        virtual SerializableObjectBuilder* operator[](Type builtType);
        virtual void addSerializableObjectBuilder(Type builtType, SerializableObjectBuilder* builderToAdd);
        virtual void removeSerializableObjectBuilder(Type builtType);
        virtual int getValueLengthLength(Type receivedType);
        virtual SerializableObject* delegateBuilding(Type typeToBuild, uint64_t valueLength, void* value);
    };


#endif // SERIALIZABLEOBJECTBUILDER_H
