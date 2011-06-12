#include "Signature.h"

Signature::Signature(nameToSet, inTypesToSet, outTypesToSet) {
	setServiceName( nameToSet);
	setInTypes( inTypesToSet);
	setOutTypes( outTypesToSet);
}
void Signature::setServiceName(String nameToSet) {
	serviceName = nameToSet;
}

String Signature::getServiceName() {
	return serviceName;
}

void Signature::setInTypes(list<Type*> inTypesToSet) {
	inTypes = inTypesToSet;
}

list<Type*> Signature::getInTypes() {
	return inTypes;
}

void Signature::setOutTypes(list<Type*> outTypesToSet) {
	outTypes = outTypesToSet;
}

list<Type*> Signature::getOutTypes() {
	return outTypes;
}
