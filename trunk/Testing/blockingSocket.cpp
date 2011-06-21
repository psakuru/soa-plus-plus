#include "../TcpIpSocket/TcpIpPassiveSocket.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

int main()
	{
	TcpIpPassiveSocket s(6000,SOMAXCONN);
	TcpIpActiveSocket* ss = s.acceptConnection();
	void* m = malloc(sizeof(int));
	m = ss->receiveMessage(sizeof(int));
	cout << "FATTO";
	return 0;
	}
