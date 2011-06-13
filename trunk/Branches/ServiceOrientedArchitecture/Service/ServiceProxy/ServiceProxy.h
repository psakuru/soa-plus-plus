#ifndef SERVICEPROXY_H
#define SERVICEPROXY_H

#include "../Service.h"

class ServiceProxy
{
public:
    void bind;
    void staticallyBind(string serviceProviderAddressToSet);
    void doService();
};

#endif // SERVICEPROXY_H
