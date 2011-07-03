#include <stdlib.h>
#include "../TcpIpSocket/TcpIpActiveSocket/TcpIpActiveSocket.h"

int main()
{
void* datiACaso = malloc(1024*1024);
TcpIpActiveSocket socket("127.0.0.1", 4000);
socket.sendMessage(datiACaso, 1024*1024);
free(datiACaso);
return 0;
}
