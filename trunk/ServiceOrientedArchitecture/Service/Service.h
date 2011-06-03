#ifndef SERVICE_H
#define SERVICE_H


//TODO

class Service
{
    private:
        list<SerializableObject*> inputParameters;
        list<SerializableObject*> outputParameters;
        string serviceID;
        //TODO Pool di thread;
        TcpIpPassiveSocket socket;
    protected:
        virtual void doService();
    public:
        Service(string serviceIDToSet,);
        virtual ~Service();
        void bindProxy();
        void staticallyBindProxy(string clientAddressToSet);
};

#endif // SERVICE_H