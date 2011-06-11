#ifndef BADREQUEST_H
#define BADREQUEST_H

#include "../../SignalSerializationStrategy.h"

class BadRequestSerializationStrategy : public SignalSerializationStrategy
{
    private:
        void signalHandler();
    public:
        Type getType();
        int getValueLengthLength();
};

typedef BadRequestSerializationStrategy BadRequest;

#endif // BADREQUEST_H
