#include "Thread.h"
#include <iostream>
using namespace std;

Thread::Thread() : boost::thread(visitor, this){}

void Thread::run()
	{
	cout << "The wonderful run() method" << endl;
	}
