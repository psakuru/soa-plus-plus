#ifndef UNKNOWNTYPE_H
#define UNKNOWNTYPE_H

#include <exception>


class UnknownType : public exception
{
public:
    virtual const char* what() const throw()
    {
        return "Unknown type";
    }
};

#endif // UNKNOWNTYPE_H
