#ifndef INTEGER_H
#define INTEGER_H

#include <stdint.h>
#include "../../TypeConstants.h"


class Integer : public SerializableObject
{
    private:
        int32_t& value;
    public:
        static const Type objectType = SERIALIZABLE_INTEGER;
        Integer(int32_t& valueToSet);
        ~Integer();
        uint64_t serialize(void** destinationBuffer);
        void deserialize(void* bufferToUse);
};

#endif // INTEGER_H
