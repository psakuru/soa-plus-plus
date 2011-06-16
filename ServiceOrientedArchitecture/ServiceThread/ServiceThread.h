#ifndef SERVICETHREAD_H
#define SERVICETHREAD_H

#include <list>
#include "Service.h"
#include "../../SerializableObjects/SerializableObjectBuilder.h"
#include <boost/thread/thread.hpp>
#include <boost/ref.hpp>
#include "../../TcpIpSocket/TcpIpSocket.h"

class ServiceThread: public Thread {

private:
	boost::mutex& mutex;
	TcpIpPassiveSocket& listeningSocket;
	TcpIpActiveSocket currentSocket;
	list<SerializableObject*> in;
	list<SerializableObject*> out;
	Service* serviceToDo;
	Functor functor;
	SerializableObject* receiveRequestParameter();
	list<SerializableObject*>* receiveRequestParameters();
	void sendParameters(list<SerializableObject*> parameterList);

public:
	void run();
	ServiceThread(boost::mutex& mutexToSet, TcpIpPassiveSocket& socketToSet,
			Service* serviceToSet);

};

#endif //SERVICETHREAD_H
