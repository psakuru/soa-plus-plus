#ifndef REAL_H
#define REAL_H

#include "../../SerializableObject.h"
#include "../../TypeConstants.h"

class Real : public SerializableObject
{
    private:
        double& value; //Per il futuro: riportare in notazione mantissa ed esp, a grandezza nota
    public:
        Real();
        Real(double& valueToSet);
        ~Real();
        Type getType();
        int getValueLengthLength();
        void operator=(const SerializableObject& objectToCopy);
        uint64_t serialize(void** destinationBuffer);
        void deserialize(uint64_t length, void* bufferToUse);
        void setValue(void* valueToSet);
        void* getValue();
};

#endif // REAL_H
