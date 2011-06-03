#ifndef STRING_H
#define STRING_H

#include "SerializableObject.h"
#include <string>
using namespace std;

class String : public SerializableObject
{
    public:
        string& value;
        String();
        String(string& valueToSet);
        /** Default destructor */
        ~String();
        void operator=(const SerializableObject&);
        uint64_t serialize(void* destinationBuffer);
        void deserialize(void* bufferToUse);
};

#endif // STRING_H
