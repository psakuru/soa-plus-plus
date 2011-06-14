/*
 * ServiceThreadPool.h
 */

#ifndef SERVICETHREADPOOL_H_
#define SERVICETHREADPOOL_H_

#include <list>
#include "../ServiceThread/ServiceThread.h"
#include "../Service/Service.h"
#include <boost/thread.hpp>
#include <boost/ref.hpp>
#include "../../TcpIpSocket/TcpIpSocket.h"

class ServiceThreadPool{

private:
	int numThread;
	boost::mutex mutex;
	TcpIpPassiveSocket& listeningSocket;
	ClonableService* serviceToDo;
	list<ServiceThread*> threadList;

public:
	void start();//TODO bool/eccezioni
	void stop();//TODO bool/eccezioni
	ServiceThreadPool(TcpIpPassiveSocket& socketToSet,
			ClonableService* serviceToSet, int numThread);

};


#endif /* SERVICETHREADPOOL_H_ */
