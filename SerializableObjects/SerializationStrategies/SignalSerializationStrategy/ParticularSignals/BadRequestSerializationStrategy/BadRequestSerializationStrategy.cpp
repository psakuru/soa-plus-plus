#include "BadRequestSerializationStrategy.h"
#include <exception>
#include <iostream>
using namespace std;

BadRequestSerializationStrategy::BadRequestSerializationStrategy() {}

BadRequestSerializationStrategy::BadRequestSerializationStrategy(BadRequestSignal& userReference) {} // Per uniformità con gli altri SerializableObject.

void BadRequestSerializationStrategy::signalHandler()
{
    /* Your signal handler here */
    cout << "Andromalius" << endl;
    //throw exception(); //TODO fare una eccezione a modo!
}

Type BadRequestSerializationStrategy::getSignalType() const
{
    return SIGNAL_BAD_REQUEST;
}

int BadRequestSerializationStrategy::getValueLengthLength()
{
    return sizeof(Type);
}
