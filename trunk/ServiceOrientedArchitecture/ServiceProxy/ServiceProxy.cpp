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

void ServiceProxy::sendParameters(list<SerializableObject*> parameterList)
    {
    list<SerializableObject*>::size_type listSize = parameterList.size();
    socket.sendMessage(&listSize, sizeov(list<SerializableObject*>::size_type));
    list<SerializableObject*>::iterator i = parameterList.begin();
    void* serializedObject = NULL;
    for(; i != parameterList.end(); i++)
        {
        uint64_t serializedObjectLength = (*i).serialize(&serializedObject);
        socket.sendMessage(serializedObject, serializedObjectLength);
        free(serializedObject);
        serializedObject = NULL;
        }
    }

list<SerializableObject*> ServiceProxy::receiveResponseParameters()
    {
    RequestStatus lastRequestStatus = *((RequestStatus)socket.receiveMessage(sizeof(RequestStatus)));
    switch(lastRequestStatus)
        {

        }
    }

void ServiceProxy::doService()
{
    sendParameters(inputParameters);
    sendParameters(outputParameters);
    list<SerializableObject*> valuesToReturn = receiveResponseParameters();
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
