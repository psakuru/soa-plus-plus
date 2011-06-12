
#include <iostream>
#include "ServiceThread.h"
#include "Functor.h"
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
using namespace std;

int main() {
	cout << "!!!Hello World!!!" << endl;
	boost::mutex m;
	ServiceThread s = ServiceThread(m);
	//Functor p;
	boost::thread prova(boost::bind(&ServiceThread::run,&s));
	return 0;
}
