#ifndef STUB_H
#define STUB_H

#include "../Service.h"

class Stub : public Service
{
protected:
    string serviceProviderAddress;
    virtual void bind();
    void protocol();
    void addParameter(SerializableObject* parameterToAdd, Direction parameterDirection);
public:
    Stub();
    Stub(string serviceIDToSet, string serviceRegistryAddressToSet);
    virtual ~Stub();
    string getServiceRegistryAddress();
    void setServiceRegistryAddress(string serviceRegistryAddressToSet);
    void rebind(); //Rifà la bind: è disponibile solo in caso di
    //emergenza al client
    void staticallyBind(string serviceProviderAddressToSet);
};

#endif // STUB_H