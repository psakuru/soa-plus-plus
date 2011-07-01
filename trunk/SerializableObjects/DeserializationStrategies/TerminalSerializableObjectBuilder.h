#ifndef TERMINALSERIALIZABLEOBJECTBUILDER_H
#define TERMINALSERIALIZABLEOBJECTBUILDER_H

#include "SerializableObjectBuilder.h"
#include <stdlib.h>
#include <iostream>
#include <typeinfo>
using namespace std;

template <typename T>
class TerminalSerializableObjectBuilder : public SerializableObjectBuilder
{
public:
    int getValueLengthLength(Type receivedType)
    {
        T dummyT;
        return dummyT.getValueLengthLength(); //Se T non implementa l' interfaccia Serializable, questo fallisce a compile-time
    }
    SerializableObject* delegateBuilding(Type typeToBuild, uint64_t valueLength, void* value)
    {
        SerializableObject* serializableObjectToReturn = new T(); //NB: se T non deriva da SerializableObject, c' è un errore a compile-time
        serializableObjectToReturn->deserialize(valueLength, value);
        free(value);
        cout << "SerializableObjectProdotto: " << (typeid(T)).name() << endl;
        return serializableObjectToReturn;
    }
};

#endif // TERMINALSERIALIZABLEOBJECTBUILDER_H
