#include "CallableObject.h"
#include <iostream>
using namespace std;

class MyThread : public CallableObject
	{
	public:
		void operator()()
			{
			for(int i = 0; i<10; i++)
			{cout << "Virtual awesomeness" << endl;}
			}
	};

int main()
	{
	MyThread T;
	boost::thread t0(T);
	boost::thread t1(T);
	boost::thread t2(T);
	boost::thread t3(T);
	boost::thread t4(T);
	boost::thread t5(T);
	boost::thread t6(T);
	boost::thread t7(T);
	boost::thread t8(T);
	boost::thread t9(T);
	boost::thread t10(T);
	boost::thread t11(T);
	boost::thread t12(T);
	boost::thread t13(T);
	boost::thread t14(T);
	t0.join();
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	t7.join();
	t8.join();
	t9.join();
	t10.join();
	t11.join();
	t12.join();
	t13.join();
	t14.join();
	return 0;
	}
