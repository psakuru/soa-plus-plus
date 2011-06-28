#include <iostream>
using namespace std;

class A
{
public:
	virtual void opertator[](int a)
	{
	cout << "Richiamo il virtual" << endl;
	this->operator[](a);
	}
}
