#include "../../ObjectInterfaces/SingletonObject/SingletonObject.h"
#include <iostream>
using namespace std;

class A
{
public:
A(){cout << "Costruttore di A" << endl;}
~A(){cout << "Distruttore di A" << endl;}
};

int main()
{
A* prova = SingletonObject<A>::getInstance();
char a = 'a';
cin >> a;
return 0;
}
