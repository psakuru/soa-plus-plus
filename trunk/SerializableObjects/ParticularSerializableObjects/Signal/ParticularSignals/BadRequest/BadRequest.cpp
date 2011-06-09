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
    const BadRequest* castReference = dynamic_cast<const BadRequest*>(&objectToCopy);
    value = castReference->value;
}

Type BadRequest::getType()
{
    return SIGNAL_BAD_REQUEST;
}

int BadRequest::getValueLengthLength()
{
    return 0;
}
