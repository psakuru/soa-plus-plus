#ifndef SIGNATURE_H
#define SIGNATURE_H

#include <list>
#include <string>
#include "../../SerializableObjects/TypeConstants.h"

class Signature {

private:
	String serviceName;
	list<Type*> inTypes;
	list<Type*> outTypes;
public:
	void setServiceName(String nameToSet);
	String getServiceName();
	void setInTypes(list<Type*> inTypesToSet);list<Type*> in getInTypes();
	void setOutTypes(list<Type*> outTypesToSet);list<Type*> in getOutTypes();
	Signature(nameToSet, inTypesToSet, outTypesToSet);
};

#endif // SIGNATURE_H
