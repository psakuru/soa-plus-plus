#ifndef INVALIDLENGTHLENGTH_H
#define INVALIDLENGTHLENGTH_H

#include <exception>


class InvalidLengthLength : public exception
{
public:
    virtual const char* what() const throw()
    {
    return "Invalid length length.";
    }
};

#endif // INVALIDLENGTHLENGTH_H
