#include "BadRequestSerializationStrategy.h"
#include <iostream>
using namespace std;

BadRequestSerializationStrategy::BadRequestSerializationStrategy(){}

BadRequestSerializationStrategy::BadRequestSerializationStrategy(BadRequestSignal& userReference)
{
    //cout << "Costruttore di BadRequestSerializationStrategy" << endl;
}

void BadRequestSerializationStrategy::signalHandler()
{
    cout << "Sono il signalHandler: prostratevi a me, e veneratemi come un dio." << endl;
    //Esempio di handling: lanciare un' eccezione!
}

Type BadRequestSerializationStrategy::getSignalType()
{
    return SIGNAL_BAD_REQUEST;
}

int BadRequestSerializationStrategy::getValueLengthLength()
{
    return 0;
}
