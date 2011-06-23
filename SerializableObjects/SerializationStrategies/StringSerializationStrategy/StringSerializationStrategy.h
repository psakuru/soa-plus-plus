#ifndef STRING_SERIALIZATION_STRATEGY_H
#define STRING_SERIALIZATION_STRATEGY_H

#include "../../SerializableObject.h"
#include <string>
#include "../../TypeConstants.h"
#include "../../GenericSerializableReferenceLayer/GenericSerializableReferenceLayer.h"
using namespace std;

class StringSerializationStrategy : public GenericSerializableReferenceLayer<string>
{
    public:
        StringSerializationStrategy();
        StringSerializationStrategy(string& valueToSet);
        StringSerializationStrategy(string* valueToSet, bool shared);
        Type getType() const;
        int getValueLengthLength();
        uint64_t serialize(void** destinationBuffer);
        void deserialize(uint64_t length, void* bufferToUse);
        string getValueTypeStringRepresentation();
};

typedef StringSerializationStrategy String;

#endif // STRING_SERIALIZATION_STRATEGY_H
