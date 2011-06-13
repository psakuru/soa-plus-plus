#include "ServiceProxy.h"

ServiceProxy::ServiceProxy()
{
    //ctor
}

ServiceProxy::~ServiceProxy()
{
    //dtor
}

void ServiceProxy::bind
{
    //Da fare
}

void ServiceProxy::staticallyBind(string serviceProviderAddressToSet)
{
    serviceProviderAddress = serviceProviderAddressToSet;
    //TODO metodino (?) per il parsing degli indirizzi
    string ipAddress = serviceProviderAddress.substr(0, serviceProviderAddress.find_first_of(':'));
    string portString = serviceProviderAddress.substr(serviceProviderAddress.find_first_of(':')+1);
    int port = atoi(portString.c_str());
    //TODO check: e se il socket era stato inizializzato?
    socket = new TcpIpActiveSocket(ipAddress, port);
}

void ServiceProxy::doService()
{
    sendParameters();
    receiveParameters();
}
