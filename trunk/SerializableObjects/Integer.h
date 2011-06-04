#ifndef INTEGER_H
#define INTEGER_H

#include <stdint.h>


class Integer : public SerializableObject
{
    private:
        int32_t& value;
    public:
        /** Default constructor */
        Integer(int32_t& valueToSet);
        /** Default destructor */
        ~Integer();
        uint64_t serialize((void*)& destinationBuffer);
        void deserialize(void* bufferToUse);
};

#endif // INTEGER_H
