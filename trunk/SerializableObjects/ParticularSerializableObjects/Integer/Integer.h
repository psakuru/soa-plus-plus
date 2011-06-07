#ifndef INTEGER_H
#define INTEGER_H

#include <stdint.h>
#include "../../TypeConstants.h"


class Integer : public SerializableObject
{
    private:
        static const Type objectType = SERIALIZABLE_INTEGER;
        int32_t& value;
    public:
        Integer(int32_t& valueToSet);
        ~Integer();
        Type getType();
        uint64_t serialize(void** destinationBuffer);
        void deserialize(void* bufferToUse);
};

#endif // INTEGER_H
