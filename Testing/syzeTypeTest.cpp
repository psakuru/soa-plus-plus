#include <iostream>
#include <list>
#include <stdint.h>
using namespace std;

int main()
{
list<int> ciao;
ciao.push_back(1);
ciao.push_back(1);
ciao.push_back(1);
ciao.push_back(1);
ciao.push_back(1);
cout << (uint32_t)ciao.size() << endl;
cout << sizeof(size_t);
for(size_t i = 0; i < 10000000000; i++)
{cout << i << " ";}
return 0;
}
