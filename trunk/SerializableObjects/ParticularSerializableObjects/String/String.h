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
        String();
        String(string& valueToSet);
        ~String();
        Type getType()
        void operator=(const SerializableObject&);
        uint64_t serialize(void** destinationBuffer);
        void deserialize(uint64_t length, void* bufferToUse);
};

#endif // STRING_H