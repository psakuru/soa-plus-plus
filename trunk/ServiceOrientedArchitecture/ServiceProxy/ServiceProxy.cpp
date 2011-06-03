#include "ServiceProxy.h"

ServiceProxy::ServiceProxy(string serviceIDToSet, string serviceRegistryAddressToSet)
    : serviceID(serviceIDToSet), serviceRegistryAddress(serviceRegistryAddressToSet)
{
    bindProxy();
}

ServiceProxy::~ServiceProxy()
{
    //dtor
}

void ServiceProxy::doService()
{
//TODO COMUNICAZIONE COL SERVICE PROVIDER (invio parametri, protocollo ecc...)
    list<SerializableObject*> valuesToReturn; //TODO inizializzare questa lista col ritorno del server
    list<SerializableObject*>::iterator i = valuesToReturn.begin();
    list<SerializableObject*>::iterator j = outputParameters.begin();
    //TODO eccezione: liste con diverso numero di parametri ecc...
    while(i != valuesToReturn.end())
    {
        *(*j) = *(*i);
        i++;
        j++;
    }
}

string ServiceProxy::getServiceRegistryAddress()
    {
    return serviceRegistryAddress;
    }

string ServiceProxy::setServiceRegistryAddress(string serviceRegistryAddressToSet)
    {
    serviceRegistryAddress = serviceRegistryAddressToSet;
    }

void ServiceProxy::bindProxy()
    {
    //TODO chiedere al serviceRegistry l' indirizzo e porta del serviceProvider che offre il service
    //TODO effettua la connessione verso il serviceProvider
    }

void staticallyBindProxy(string serviceProviderAddressToSet)
    {
    //TODO effettua la connessione verso il serviceProvider settando tutto opportunamente
    }
