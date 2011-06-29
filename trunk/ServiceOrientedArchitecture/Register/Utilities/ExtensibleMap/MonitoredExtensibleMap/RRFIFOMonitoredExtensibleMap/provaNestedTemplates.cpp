#include <iostream>
using namespace std;

template <typename T>
class Nested
{
public:
T value;
};

template <typename T, typename V>
class Container
{
public:
T arrayT[4];
V arrayV[4];
};

template < template<typename, typename> class T>
class Biohazard
{
public:
T<int, char> valore;
};

int main()
{
Biohazard< Container > ciao;
cout << ciao.valore.arrayT[0] << endl;
ciao.valore.arrayV[0] = 'a';
cout << ciao.valore.arrayV[0] << endl;
return 0;
}
