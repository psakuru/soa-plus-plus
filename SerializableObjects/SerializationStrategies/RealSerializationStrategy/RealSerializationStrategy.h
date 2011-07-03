#ifndef REAL_SERIALIZATION_STRATEGY_H
#define REAL_SERIALIZATION_STRATEGY_H

#include "../../SerializableObject.h"
#include "../../TypeConstants.h"
#include "../../GenericSerializableReferenceLayer/GenericSerializableReferenceLayer.h"

class RealSerializationStrategy : public GenericSerializableReferenceLayer<double>
{
public:
    RealSerializationStrategy();
    RealSerializationStrategy(double& userReferenceToSet);
    RealSerializationStrategy(double* userReferenceToSet, bool shared);
    Type getType() const;
    int getValueLengthLength();
    uint64_t serialize(void** destinationBuffer);
    void deserialize(uint64_t length, void* bufferToUse);
    string getValueTypeStringRepresentation();
};

typedef RealSerializationStrategy Real;

#endif // REAL_SERIALIZATION_STRATEGY_H
