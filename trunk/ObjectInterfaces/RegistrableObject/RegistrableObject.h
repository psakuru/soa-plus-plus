#ifndef REGISTRABLEOBJECT_H
#define REGISTRABLEOBJECT_H

#include <string>
using namespace std;

class RegistrableObject
{
public:
    virtual string getRegistrationInfo() = 0;
};

#endif // REGISTRABLEOBJECT_H