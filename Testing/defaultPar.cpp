#include <iostream>
using namespace std;

class A
{
protected:
int a;
public:
A(int v) {a=v;}
void method(int prova = 9)
{
cout << prova;
}
};

int main()
{
A a(7);
a.method();
a.method(9);
return 0;
}
