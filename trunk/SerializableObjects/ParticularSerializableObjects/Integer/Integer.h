#ifndef INTEGER_H
#define INTEGER_H

#include <stdint.h>
#include "../../TypeConstants.h"
#include "../../SerializableObject.h"


class Integer : public SerializableObject
{
    private:
        static const Type objectType = SERIALIZABLE_INTEGER;
        int32_t& value;
    public:
        Integer();
        Integer(int32_t& valueToSet);
        ~Integer();
        Type getType();
        uint64_t serialize(void** destinationBuffer);
        void deserialize(uint64_t length, void* bufferToUse);
};

#endif // INTEGER_H
