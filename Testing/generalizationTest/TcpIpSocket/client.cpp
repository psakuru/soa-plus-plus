#include "TcpIpActiveSocket.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

int main()
	{
	TcpIpActiveSocket s("127.0.0.1", 4000);
	char* message = "BUONGIORNO";
	cout << "Client: invio il messaggio\0" << endl;
	s.sendMessage(message, 11);
	cout << "Client: messaggio inviato" << endl;
	char* ritorno;
	ritorno = (char*)s.receiveMessage(5);
	cout << ritorno << "!!!!";
	free(ritorno);
	return 0;
	}
