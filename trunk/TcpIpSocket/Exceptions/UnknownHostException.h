#ifndef UNKNOWNHOSTEXCEPTION_H
#define UNKNOWNHOSTEXCEPTION_H

#include <exception>


class UnknownHostException : public exception
{
    public:
    virtual const char* what() const throw()
    {
    return "Cannot retrieve host from the specified URL/IP address.";
    }
};

#endif // UNKNOWNHOSTEXCEPTION_H
