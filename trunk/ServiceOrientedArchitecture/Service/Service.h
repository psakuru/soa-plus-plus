#ifndef SERVICE_H
#define SERVICE_H

#include "../Utilities/PointerList/PointerList.h"
#include "../../SerializableObjects/SerializableObject.h"
#include "../../SerializableObjects/DeserializationStrategies/SerializableObjectBuilder.h"
#include "../../TcpIpSocket/TcpIpActiveSocket.h"
#include <string>
using namespace std;

typedef PointerList<SerializableObject*> SerializableObjectList;
//Lista di puntatori a SerializableObject, fa la delete sui puntatori quando distrutta

enum Direction {IN, OUT, INOUT, OUTIN};

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
    virtual void sendParameters();
    virtual void receiveParameters();
    SerializableObject* receiveParameter();
    virtual void protocol() = 0;
    virtual void bind() = 0;
    virtual void addParameter(SerializableObject* parameterToAdd, Direction parameterDirection) = 0;
    void updateServiceID(SerializableObject* parameterToAdd, Direction parameterDirection);
public:
	Service();
    Service(string serviceIDToSet);
    virtual ~Service();
};

#endif // SERVICE_H
