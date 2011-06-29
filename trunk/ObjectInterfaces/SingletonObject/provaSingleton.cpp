#include "SingletonObject.h"
#include <iostream>
using namespace std;

int main()
{
	cout << "SingletonObject<int>::getInstance(): " << *(SingletonObject<double>::getInstance()) << endl;
	return 0;
}
