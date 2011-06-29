#include <iostream>
using namespace std;

class A
{
public:
int val;
A(int v) : val(v){}
void print(){cout << val << endl;}
};

class B : public A
{
public:
int valB;
B(int vA, int vB) : A(vA), valB(vB){}
};

template <typename T>
class C : virtual public T
{
public:
C(int vA, int vB) : T(vA, vB){}
};

class D : public C<B>
{
public:
D(int vA, int vB) : B(vA, vB), C<B>(vA, vB){}
};

int main()
{
D c(2,7);
c.print();
return 0;
}
