#include "Service.h"

Service::Service(Signature signatureToSet) {
	setSignature(signatureToSet);
}

void Service::setSignature(Signature signatureToSet) {

	signature = signatureToSet;
}

Signature Service::getSignature() {

	return signature;
}
