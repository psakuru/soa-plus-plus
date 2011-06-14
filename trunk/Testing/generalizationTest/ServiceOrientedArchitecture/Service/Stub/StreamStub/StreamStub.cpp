#include "StreamStub.h"
#include "../../../../SerializableObjects/SerializationStrategies/IntegerSerializationStrategy/IntegerSerializationStrategy.h"
#include "../../../../SerializableObjects/SerializationStrategies/RealSerializationStrategy/RealSerializationStrategy.h"
#include "../../../../SerializableObjects/SerializationStrategies/StringSerializationStrategy/StringSerializationStrategy.h"
#include "../../../../SerializableObjects/SerializationStrategies/RawByteBufferSerializationStrategy/RawByteBufferSerializationStrategy.h"
#include <iostream>
using namespace std;

StreamStub::StreamStub() {}

StreamStub::StreamStub(string serviceIDToSet, string serviceRegistryAddressToSet)
    : Stub(serviceIDToSet, serviceRegistryAddressToSet)
    {
    }

StreamStub::~StreamStub() {}

void StreamStub::operator<<(int& value)
{
    SerializableObject* objectToPushIntoList = new Integer(value);
    outputParameters.push_back(objectToPushIntoList);
}

void StreamStub::operator<<(double& value)
{
    SerializableObject* objectToPushIntoList = new Real(value);
    outputParameters.push_back(objectToPushIntoList);
}

void StreamStub::operator<<(string& value)
{
    SerializableObject* objectToPushIntoList = new String(value);
    outputParameters.push_back(objectToPushIntoList);
}
void StreamStub::operator<<(ByteArray& value)
{
    SerializableObject* objectToPushIntoList = new RawByteBuffer(value);
    outputParameters.push_back(objectToPushIntoList);
}

void StreamStub::operator<<(BadRequestSignal& value)
{
    SerializableObject* objectToPushIntoList = new BadRequest(value);
    outputParameters.push_back(objectToPushIntoList);
}

void StreamStub::operator>>(int& value)
{
    SerializableObject* objectToPushIntoList = new Integer(value);
    inputParameters.push_back(objectToPushIntoList);
}

void StreamStub::operator>>(double& value)
{
    SerializableObject* objectToPushIntoList = new Real(value);
    inputParameters.push_back(objectToPushIntoList);
}

void StreamStub::operator>>(string& value)
{
    SerializableObject* objectToPushIntoList = new String(value);
    inputParameters.push_back(objectToPushIntoList);
}
void StreamStub::operator>>(ByteArray& value)
{
    SerializableObject* objectToPushIntoList = new RawByteBuffer(value);
    inputParameters.push_back(objectToPushIntoList);

}

void StreamStub::operator>>(BadRequestSignal& value)
{
    cout << "operator<< : wrapping del BadRequestSignal" << endl;
    SerializableObject* objectToPushIntoList = new BadRequest(value);
    inputParameters.push_back(objectToPushIntoList);
    cout << "BadRequestSignal wrappato in BadRequestSerializationStrategy e inserito nella lista out" << endl;
}
