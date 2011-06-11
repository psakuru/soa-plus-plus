#include "BadRequest.h"

BadRequest::BadRequest()
{
    //ctor
}

BadRequest::~BadRequest()
{
    //dtor
}

void BadRequest::signalHandler()
{
    //cout << "Sono il signalHandler" << endl;
}

void BadRequest::operator=(const SerializableObject& objectToCopy)
{
}

Type BadRequest::getType()
{
    return SIGNAL_BAD_REQUEST;
}

int BadRequest::getValueLengthLength()
{
    return 0;
}
