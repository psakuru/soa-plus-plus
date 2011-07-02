#ifndef INVALIDADDRESSEXCEPTION_H
#define INVALIDADDRESSEXCEPTION_H

#include <exception>


class InvalidAddressException : public exception
{
public:
    virtual const char* what() const throw()
    {
        return "The specified address in invalid";
    }
};

#endif // INVALIDADDRESSEXCEPTION_H
