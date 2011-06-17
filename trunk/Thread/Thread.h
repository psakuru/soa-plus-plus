#ifndef THREAD_H
#define THREAD_H
#include <boost/thread.hpp>

//COMPILARE CON  -Wall -g -lboost_thread -lpthread

class Thread : public boost::thread
	{
	private:
		class ThreadVisitor
            {
            public:
                void operator()(Thread* threadToVisit)
                    {
                        threadToVisit->run();
                    }
            } visitor;
	public:
		Thread();
		virtual void run() = 0;
	};

#endif //THREAD_H
