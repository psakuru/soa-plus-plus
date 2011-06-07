#ifndef STRING_H
#define STRING_H

#include "SerializableObject.h"
#include <string>
#include "../../TypeConstants.h"
using namespace std;

class String : public SerializableObject
{
    private:
        static const Type objectType = SERIALIZABLE_STRING;
        string& value;
    public:
        String();
        String(string& valueToSet);
        ~String();
        Type getType()
        void operator=(const SerializableObject&);
        uint64_t serialize(void** destinationBuffer);
        void deserialize(void* bufferToUse);
};

#endif // STRING_H
