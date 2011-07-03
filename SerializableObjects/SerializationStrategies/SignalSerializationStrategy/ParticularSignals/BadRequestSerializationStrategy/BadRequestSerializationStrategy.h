#ifndef BADREQUEST_SERIALIZATION_STRATEGY_H
#define BADREQUEST_SERIALIZATION_STRATEGY_H

#include "../../SignalSerializationStrategy.h"
#include "../../Utilities/BadRequestSignal/BadRequestSignal.h"

class BadRequestSerializationStrategy : public SignalSerializationStrategy
{
private:
    void signalHandler();
public:
    BadRequestSerializationStrategy();
    BadRequestSerializationStrategy(BadRequestSignal& userReference);
    Type getSignalType() const;
    int getValueLengthLength();
};

typedef BadRequestSerializationStrategy BadRequest;

#endif // BADREQUEST_SERIALIZATION_STRATEGY_H
