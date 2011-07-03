#ifndef INVALIDPARAMETERLISTSIZE_H
#define INVALIDPARAMETERLISTSIZE_H

#include <exception>


class InvalidParameterListSize : public exception
{
public:
    virtual const char* what() const throw()
    {
    return "Invalid parameter list length";
    }
};

#endif // INVALIDPARAMETERLISTSIZE_H
