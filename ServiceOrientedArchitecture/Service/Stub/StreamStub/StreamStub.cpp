#include "StreamStub.h"
#include "../../../../SerializableObjects/SerializationStrategies/IntegerSerializationStrategy/IntegerSerializationStrategy.h"
#include "../../../../SerializableObjects/SerializationStrategies/RealSerializationStrategy/RealSerializationStrategy.h"
#include "../../../../SerializableObjects/SerializationStrategies/StringSerializationStrategy/StringSerializationStrategy.h"
#include "../../../../SerializableObjects/SerializationStrategies/RawByteBufferSerializationStrategy/RawByteBufferSerializationStrategy.h"
#include <iostream>
using namespace std;

// NB: codice replicatissimo!
StreamStub::StreamStub() {}

StreamStub::StreamStub(string serviceIDToSet, string serviceRegistryAddressToSet)
    : Stub(serviceIDToSet, serviceRegistryAddressToSet) {}

StreamStub::~StreamStub() {}

void StreamStub::operator<<(int& value)
{
    /*SerializableObject* objectToPushIntoList = new Integer(value);
    outputParameters.push_back(objectToPushIntoList);*/
    addParameter(new Integer(value), OUT);
}

void StreamStub::operator<<(double& value)
{
    /*SerializableObject* objectToPushIntoList = new Real(value);
    outputParameters.push_back(objectToPushIntoList);*/
    addParameter(new Real(value), OUT);
}

void StreamStub::operator<<(string& value)
{
    /*SerializableObject* objectToPushIntoList = new String(value);
    outputParameters.push_back(objectToPushIntoList);*/
    addParameter(new String(value), OUT);
}

void StreamStub::operator<<(ByteArray& value)
{
    /*SerializableObject* objectToPushIntoList = new RawByteBuffer(value);
    outputParameters.push_back(objectToPushIntoList);*/
    addParameter(new RawByteBuffer(value), OUT);
}

void StreamStub::operator<<(BadRequestSignal& value)
{
    /*SerializableObject* objectToPushIntoList = new BadRequest(value);
    outputParameters.push_back(objectToPushIntoList);*/
    addParameter(new BadRequest(value), OUT);
}

void StreamStub::operator>>(int& value)
{
    /*SerializableObject* objectToPushIntoList = new Integer(value);
    inputParameters.push_back(objectToPushIntoList);*/
    addParameter(new Integer(value), OUTIN);
}

void StreamStub::operator>>(double& value)
{
    /*SerializableObject* objectToPushIntoList = new Real(value);
    inputParameters.push_back(objectToPushIntoList);*/
    addParameter(new Real(value), OUTIN);
}

void StreamStub::operator>>(string& value)
{
    /*SerializableObject* objectToPushIntoList = new String(value);
    inputParameters.push_back(objectToPushIntoList);*/
    addParameter(new String(value), OUTIN);
}
void StreamStub::operator>>(ByteArray& value)
{
    /*SerializableObject* objectToPushIntoList = new RawByteBuffer(value);
    inputParameters.push_back(objectToPushIntoList);*/
    addParameter(new RawByteBuffer(value), OUTIN);

}

void StreamStub::operator>>(BadRequestSignal& value)
{

    /*SerializableObject* objectToPushIntoList = new BadRequest(value);
    inputParameters.push_back(objectToPushIntoList);*/

    addParameter(new BadRequest(value), OUTIN);
}
