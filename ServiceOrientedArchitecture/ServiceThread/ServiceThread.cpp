#include "ServiceThread.h"

//TODO TUTTO CODICE REPLICATO, METTERLO NELLA LIBRERIA!!!

ServiceThread::ServiceThread(boost::mutex& mutexToSet,
		TcpIpPassiveSocket& socketToSet, Service* serviceToSet) :
	listeningSocket(socketToSet), mutex(mutexToSet),
			serviceToDo(serviceToSet) {
	//TODO BOH!!!
	buildersHierarchy.addSerializableObjectBuilder(SERIALIZABLE_INTEGER,
			new TerminalSerializableObjectBuilder<Integer> ());
	buildersHierarchy.addSerializableObjectBuilder(SERIALIZABLE_REAL,
			new TerminalSerializableObjectBuilder<Real> ());
	buildersHierarchy.addSerializableObjectBuilder(SERIALIZABLE_STRING,
			new TerminalSerializableObjectBuilder<String> ());
	buildersHierarchy.addSerializableObjectBuilder(
			SERIALIZABLE_RAW_BYTE_BUFFER,
			new TerminalSerializableObjectBuilder<RawByteBuffer> ());
	buildersHierarchy.addSerializableObjectBuilder(SERIALIZABLE_SIGNAL,
			new SignalBuilder());
	buildersHierarchy[SERIALIZABLE_SIGNAL]->addSerializableObjectBuilder(
			SIGNAL_BAD_REQUEST, new TerminalSerializableObjectBuilder<
					BadRequest> ());
	//ALTRI SEGNALI
}

SerializableObject* ServiceThread::receiveRequestParameter() {
	//TODO eccezioni!!!!
	Type* receivedTypePointer = ((Type*) currentSocket->receiveMessage(
			sizeof(Type)));
	Type receivedType = *receivedTypePointer;
	cout << "Tipo ricevuto: " << receivedType << endl;
	free(receivedTypePointer);
	int valueLengthLength =
			buildersHierarchy.getValueLengthLength(receivedType);
	cout << "Lunghezza del campo length da ricevere: " << valueLengthLength
			<< endl;
	uint64_t
			valueLength =
					(valueLengthLength == 0) ? 0
							: (valueLengthLength == sizeof(uint8_t)) ? *((uint8_t*) currentSocket->receiveMessage(
									sizeof(uint8_t)))
									: (valueLengthLength == sizeof(uint16_t)) ? *((uint16_t*) currentSocket->receiveMessage(
											sizeof(uint16_t)))
											: (valueLengthLength
													== sizeof(uint32_t)) ? *((uint32_t*) currentSocket->receiveMessage(
													sizeof(uint32_t)))
													: (valueLengthLength
															== sizeof(uint64_t)) ? *((uint64_t*) currentSocket->receiveMessage(
															sizeof(uint64_t)))
															: 0;
	cout << "Campo length: " << valueLength << endl;
	void* value = (valueLength == 0) ? NULL : currentSocket->receiveMessage(
			valueLength);
	return buildersHierarchy.delegateBuilding(receivedType, valueLength, value); //NB: la guild deve fare la free del value
}

list<SerializableObject*>* ServiceThread::receiveRequestParameters() {
	list<SerializableObject*>* requestParameters =
			new list<SerializableObject*> ;
	list<SerializableObject*>::size_type listSize = requestParameters.size();
	for (int i = 0; i < listSize; i++) {
		//TODO controllo sul tipo ritornato dal server!
		requestParameters->push_back(receiveRequestParameter());
	}
	return requestParameters; //Ritorno per puntatore!
}

void ServiceThread::sendParameters(list<SerializableObject*> parameterList) {
	list<SerializableObject*>::size_type listSize = parameterList.size();
	currentSocket->sendMessage(&listSize,
			sizeof(list<SerializableObject*>::size_type));
	list<SerializableObject*>::iterator i = parameterList.begin();
	void* serializedObject = NULL;
	for (; i != parameterList.end(); i++) {
		uint64_t serializedObjectLength = (*i)->serialize(&serializedObject);
		currentSocket->sendMessage(serializedObject, serializedObjectLength);
		free(serializedObject);
		serializedObject = NULL;
	}
}

void ServiceThread::run() {
	detach();
	while (1) {
		mutex.lock(); // tornello
		currentSocket = listeningSocket.acceptConnection();
		mutex.unlock();
		in = *(receiveRequestParameters());
		out = *(receiveRequestParameters());
		ServiceToDo->doService(in, out);
		sendParameters(out);
		in.clear();
		out.clear();
	}

}
