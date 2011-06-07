#ifndef STRING_H
#define STRING_H

#include "SerializableObject.h"
#include <string>
#include "../../TypeConstants.h"
using namespace std;

class String : public SerializableObject
{
    private:
        string& value;
    public:
        static const Type objectType = SERIALIZABLE_STRING;
        String();
        String(string& valueToSet);
        ~String();
        void operator=(const SerializableObject&);
        uint64_t serialize(void** destinationBuffer);
        void deserialize(void* bufferToUse);
};

#endif // STRING_H
