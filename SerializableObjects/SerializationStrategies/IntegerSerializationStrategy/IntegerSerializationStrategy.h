#ifndef INTEGER_SERIALIZATION_STRATEGY_H
#define INTEGER_SERIALIZATION_STRATEGY_H

#include <stdint.h>
#include "../../TypeConstants.h"
#include "../../SerializableObject.h"
#include "../../GenericSerializableReferenceLayer/GenericSerializableReferenceLayer.h"


class IntegerSerializationStrategy : public GenericSerializableReferenceLayer<int32_t>
{
public:
    IntegerSerializationStrategy();
    IntegerSerializationStrategy(int32_t& valueToSet);
    IntegerSerializationStrategy(int32_t* userReferenceToSet, bool shared);
    Type getType() const;
    int getValueLengthLength();
    uint64_t serialize(void** destinationBuffer);
    void deserialize(uint64_t length, void* bufferToUse);
    string getValueTypeStringRepresentation();
};

typedef IntegerSerializationStrategy Integer;

#endif // INTEGER_SERIALIZATION_STRATEGY_H
