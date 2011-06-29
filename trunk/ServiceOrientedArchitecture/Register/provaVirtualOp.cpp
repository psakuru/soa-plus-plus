#include <iostream>
using namespace std;

class A
{
public:
	virtual void metodoA()
	{
	cout << "Richiamo il metodoB" << endl;
	metodoB();
	}
	virtual void metodoB()
	{
	cout << "MetodoB in classe base" << endl;
	}
};

class B : public A
{
public:
virtual void metodoB()
{
cout << "MetodoB in classe derivata" << endl;
}
};


int main()
{
B ciao;
ciao.metodoA();
return 0;
}
