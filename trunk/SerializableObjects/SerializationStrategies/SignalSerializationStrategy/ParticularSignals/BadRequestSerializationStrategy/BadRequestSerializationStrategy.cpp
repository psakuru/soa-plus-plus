#include "BadRequestSerializationStrategy.h"

void BadRequestSerializationStrategy::signalHandler()
{
    //cout << "Sono il signalHandler" << endl;
    //Esempio di handling: lanciare un' eccezione!
}

Type BadRequestSerializationStrategy::getType()
{
    return SIGNAL_BAD_REQUEST;
}

int BadRequestSerializationStrategy::getValueLengthLength()
{
    return 0;
}
