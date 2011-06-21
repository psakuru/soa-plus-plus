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
        //cout << "TerminalSerializableObjectBuilder: getValueLengthLength(Type)" << endl;
        //cout << "Istanziazione: T = " << (typeid(T)).name() << endl;
        T dummyT;
        return dummyT.getValueLengthLength();
    }
    SerializableObject* delegateBuilding(Type typeToBuild, uint64_t valueLength, void* value)
    {
        //TODO controllare che T sia derivato da SerializableObject
        //cout << "TerminalSerializableObjectBuilder: delegateBuilding(Type)" << endl;
        //cout << "Istanziazione: T = " << (typeid(T)).name() << endl;
        SerializableObject* serializableObjectToReturn = new T();
        serializableObjectToReturn->deserialize(valueLength, value);
        free(value);
        return serializableObjectToReturn;
    }
};

#endif // TERMINALSERIALIZABLEOBJECTBUILDER_H
