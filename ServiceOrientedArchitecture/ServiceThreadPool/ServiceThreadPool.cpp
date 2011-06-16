/*
 * ServiceThreadPool.cpp
 */

void ServiceThreadPool::start(){
	//TODO exceptions
	for(int i=0;i<numThread;i++){
		//in caso si riuscisse a farla derivare da boost::thread::thread
		//basta crearli, poi pensa a tutto il costruttore. Altrimenti codice seguente:
		//Service* particularServiceToDo = serviceToDo->newIstance();
		//ServiceThread sThread = ServiceThread(mutex,listeningSocket,particularServiceToDo);
		//boost::thread thread(boost::bind(&ServiceThread::run,&sThread));
		//se non funziona la bind bisogna fare il Functor.
		Service* particularServiceToDo = serviceToDo->newIstance();
		ServiceThread thread = ServiceThread(mutex,listeningSocket,particularServiceToDo);
		threadList.push_back(&thread);
	}
}

void ServiceThreadPool::stop(){
	//TODO exceptions
	while(!threadList.empty()){
		list<ServiceThread*>::iterator i = threadList.begin();
		(*i)->interrupt();
		threadList.pop_front();
		i++;
	}
}

ServiceThreadPool::ServiceThreadPool(TcpIpPassiveSocket& socketToSet,
		Service* serviceToSet, int numThreadToSet) : listeningSocket(socket), serviceToDo(serviceToSet), numThread(numThreadToSet){
}
