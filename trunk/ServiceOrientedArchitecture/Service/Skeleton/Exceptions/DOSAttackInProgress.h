#ifndef DOSATTACKINPROGRESS_H
#define DOSATTACKINPROGRESS_H

#include <exception>


class DOSAttackInProgress : public exception
{
public:
    virtual const char* what() const throw()
    {
        return "DOS attack in progress";
    }
};

#endif // DOSATTACKINPROGRESS_H
