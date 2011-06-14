#include "TcpIpPassiveSocket.h"
#include <iostream>
#include <string>
using namespace std;

int main()
	{
	TcpIpPassiveSocket l(4000,5);
	cout << "Server: socket in listening, faccio la accept" << endl;
	TcpIpActiveSocket* s = l.acceptConnection();
	cout << "Server: accept passata, faccio la read" << endl;
	string message = (char*)(s->receiveMessage(11));
	cout << "Server: messaggio ricevuto: " << message << endl;
	char* invia = "Ciao\0";
	s->sendMessage(invia, 5);
	}
