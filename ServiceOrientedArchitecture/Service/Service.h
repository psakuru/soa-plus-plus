#ifndef SERVICE_H
#define SERVICE_H

#include "Signature.h"
#include <list>

class Service {

private:
	Signature signature;
public:
	virtual void doService(list<SerializableObject*> in, list<
			SerializableObject*> out);
	void setSignature(Signature signature);
	Signature getSignature();
	Service(Signature signatureToSet);
}

#endif // SERVICE_H
