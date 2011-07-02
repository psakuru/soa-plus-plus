#include "BadRequestSerializationStrategy.h"
#include <iostream>
using namespace std;

BadRequestSerializationStrategy::BadRequestSerializationStrategy(){}

BadRequestSerializationStrategy::BadRequestSerializationStrategy(BadRequestSignal& userReference)
{

}

void BadRequestSerializationStrategy::signalHandler()
{
    cout << "Sono il signalHandler: prostratevi a me, e veneratemi come un dio." << endl;
}

Type BadRequestSerializationStrategy::getSignalType() const
{
    return SIGNAL_BAD_REQUEST;
}

int BadRequestSerializationStrategy::getValueLengthLength()
{
    return 0;
}
