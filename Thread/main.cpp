#include "Thread.h"
#include <iostream>
using namespace std;

class MyThread : public Thread
	{
	public:
		void run()
			{
			cout << "Virtual awesomeness" << endl;
			}
	};

int main()
	{
	MyThread t;
	t.join();
	return 0;
	}
