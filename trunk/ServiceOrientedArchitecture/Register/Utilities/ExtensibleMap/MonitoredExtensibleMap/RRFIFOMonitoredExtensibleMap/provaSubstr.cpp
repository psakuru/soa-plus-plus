#include <string>
#include <iostream>
using namespace std;

int main()
{
	string entry = "cioajdojvsv@saodvhasdv";
	cout << entry.substr(0, entry.find_first_of('@')) << endl << entry.substr(entry.find_first_of('@')+1) << endl;
	return 0;
}
