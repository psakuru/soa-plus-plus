#ifndef STUB_H
#define STUB_H

#include "../Service.h"

class Stub : public Service
{
protected:
	string serviceProviderAddress;
    void bind();
    void protocol();
public:
    Stub();
    Stub(string serviceIDToSet, string serviceRegistryAddressToSet);
    virtual ~Stub();
    string getServiceRegistryAddress();
    string setServiceRegistryAddress(string serviceRegistryAddressToSet);
    void rebind(); //Rifà la bind: è disponibile solo in caso di
    //emergenza al client
    void staticallyBind(string serviceProviderAddressToSet);
};

#endif // STUB_H
