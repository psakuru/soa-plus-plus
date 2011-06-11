#ifndef BADREQUEST_H
#define BADREQUEST_H

#include "../../Signal.h"

class BadRequest : public Signal
{
    private:
        void signalHandler();
    public:
        BadRequest();
        ~BadRequest();
        void operator=(const SerializableObject&);
        Type getType();
        int getValueLengthLength();
};

#endif // BADREQUEST_H
