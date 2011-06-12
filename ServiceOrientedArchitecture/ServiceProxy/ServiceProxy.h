#ifndef SERVICEPROXY_H
#define SERVICEPROXY_H

#include <list>
#include <string>
#include "../../TcpIpSocket/TcpIpActiveSocket.h"
#include "../../SerializableObjects/DeserializationStrategies/SerializableObjectBuilder.h"
#include "../../SerializableObjects/Utilities/ByteArray/ByteArray.h"
#include "../../SerializableObjects/SerializationStrategies/SignalSerializationStrategy/Utilities/BadRequestSignal/BadRequestSignal.h"

class ServiceProxy
{
    private:
        list<SerializableObject*> inputParameters;
        list<SerializableObject*> outputParameters;
        string serviceID;
        string serviceRegistryAddress;
        string serviceProviderAddress;
        TcpIpActiveSocket* socket;
        SerializableObjectBuilder buildersHierarchy;
        void defaultBuildersHierarchyInit();
        void sendParameters(list<SerializableObject*> parameterList);
        list<SerializableObject*>* receiveResponseParameters();
        SerializableObject* receiveResponseParameter();
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
        void doService();
    public:
        ServiceProxy();
        ServiceProxy(string serviceIDToSet, string serviceRegistryAddressToSet);
        virtual ~ServiceProxy();
        string getServiceRegistryAddress();
        string setServiceRegistryAddress(string serviceRegistryAddressToSet);
        void bindProxy();
        void staticallyBindProxy(string serviceProviderAddressToSet);
};

#endif // SERVICEPROXY_H
