#ifndef INCOMPATIBLETYPES_H
#define INCOMPATIBLETYPES_H

#include <exception>


class IncompatibleTypes : public exception
{
public:
    virtual const char* what() const throw()
    {
        return "Incompatible types";
    }
};

#endif // INCOMPATIBLETYPES_H
