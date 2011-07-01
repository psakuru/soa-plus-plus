#include <iostream>
using namespace std;

class A
{
public:
int valore;
A(int v) : valore(v){}
A metodo()
{
return A(7);
}
};

int main()
{
A a(0);
cout << (a.metodo()).valore;
return 0; 
}
