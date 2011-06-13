#ifndef SERVICE_H
#define SERVICE_H

#include <boost/ptr_container/ptr_list.hpp>

typedef boost::ptr_list<SerializableObject> SerializableObjectList;
//Lista di puntatori a SerializableObject, fa la delete sui puntatori quando distrutta

class Service
{
protected:
    SerializableObjectList inputParameters;
    SerializableObjectList outputParameters;
    string serviceID;
    string serviceRegistryAddress;
    TcpIpActiveSocket* socket;
    SerializableObjectBuilder buildersHierarchy;
    void defaultBuildersHierarchyInit();
    void sendParameters();
    void receiveParameters();
    void receiveParameter();
    virtual void doService() = 0;
    virtual void bind() = 0;
public:
    Service(string serviceIDToSet, string serviceRegistryAddressToSet);
    string getServiceRegistryAddress();
    string setServiceRegistryAddress(string serviceRegistryAddressToSet);
};

#endif // SERVICE_H
