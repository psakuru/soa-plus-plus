#ifndef SERVICEPROXY_H
#define SERVICEPROXY_H


class ServiceProxy
{
    private:
        list<SerializableObject*> inputParameters;
        list<SerializableObject*> outputParameters;
        string serviceID;
        string serviceRegistryAddress;
        string serviceProviderAddress;
        TcpIpActiveSocket socket;
        Guild<SerializableObject> buildersGuild;
        void sendParameters(list<SerializableObject*> parameterList);
        list<SerializableObject*>* receiveResponseParameters();
        SerializableObject* receiveResponseParameter();
    protected:
        void doService();
    public:
        ServiceProxy(string serviceIDToSet, string serviceRegistryAddressToSet);
        virtual ~ServiceProxy();
        string getServiceRegistryAddress();
        string setServiceRegistryAddress(string serviceRegistryAddressToSet);
        void bindProxy();
        void staticallyBindProxy(string serviceProviderAddressToSet);
};

#endif // SERVICEPROXY_H
