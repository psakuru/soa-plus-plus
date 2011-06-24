#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <strings.h>
#include <arpa/inet.h>
#include <string>
using namespace std;

int main()
	{
	char* hostName = new char[256];
	gethostname(hostName,256);
	cout << gethostbyname(hostName)->h_name;
	delete[] hostName;
	return 0;
	}
