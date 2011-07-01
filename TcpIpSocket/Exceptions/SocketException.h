#ifndef SOCKETEXCEPTION_H
#define SOCKETEXCEPTION_H

#include <exception>
#include <string.h>
#include <errno.h>


class SocketException : public exception
{
    public:
    virtual const char* what() const throw()
    {
    return strerror(errno);
    }
};

#endif // SOCKETEXCEPTION_H
