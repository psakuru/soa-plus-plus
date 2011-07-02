#ifndef PARAMETERDIRECTIONEXCEPTION_H
#define PARAMETERDIRECTIONEXCEPTION_H

#include <exception>


class ParameterDirectionException : public exception
{
public:
    virtual const char* what() const throw()
    {
        return "Invalid parameter direction";
    }
};

#endif // PARAMETERDIRECTIONEXCEPTION_H
