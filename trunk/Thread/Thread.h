#ifndef THREAD_H
#define THREAD_H
#include <boost/thread.hpp>

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
		void run();
	};

#endif //THREAD_H
