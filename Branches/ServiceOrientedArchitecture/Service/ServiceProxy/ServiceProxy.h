#ifndef SERVICEPROXY_H
#define SERVICEPROXY_H

#include "../Service.h"

class ServiceProxy : public Service
{
protected:
    virtual void operator<<(int& value);
    virtual void operator<<(double& value);
    virtual void operator<<(string& value);
    virtual void operator<<(ByteArray& value);
    virtual void operator<<(BadRequestSignal& value);
    virtual void operator>>(int& value);
    virtual void operator>>(double& value);
    virtual void operator>>(string& value);
    virtual void operator>>(ByteArray& value);
    virtual void operator>>(BadRequestSignal& value);
public:
    ServiceProxy();
    ServiceProxy(string serviceIDToSet, string serviceRegistryAddressToSet);
    virtual ~ServiceProxy();
    void bind;
    void staticallyBind(string serviceProviderAddressToSet);
    void doService();
};

#endif // SERVICEPROXY_H
