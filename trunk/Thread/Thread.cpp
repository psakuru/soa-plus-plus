#include "Thread.h"

Thread::Thread() : boost::thread(visitor, this){}
