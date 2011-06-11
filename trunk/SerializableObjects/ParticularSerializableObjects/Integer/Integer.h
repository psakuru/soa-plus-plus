#ifndef INTEGER_H
#define INTEGER_H

#include <stdint.h>
#include "../../TypeConstants.h"
#include "../../SerializableObject.h"


class Integer : public SerializableObject
{
    private:
        int32_t& value;
    public:
        Integer();
        Integer(int32_t& valueToSet);
        ~Integer();
        Type getType();
        int getValueLengthLength();
        void operator=(const SerializableObject& objectToCopy);
        uint64_t serialize(void** destinationBuffer);
        void deserialize(uint64_t length, void* bufferToUse);
        void setValue(void* valueToSet);
        void* getValue();
};

#endif // INTEGER_H
