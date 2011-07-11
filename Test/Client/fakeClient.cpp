#include "../../ServiceOrientedArchitecture/Service/Stub/StreamStub/StreamStub.h"
#include <exception>
#include "GetImage.h"
#include <string>
using namespace std;

/* Lo scopo del test è quello di mostrare le possibilità
 * di invio di segnali tra servizi.
 * Un segnale è un oggetto serializzabile la cui deserializzazione
 * ha come effetto l' invocazione di un signal handler.
 */
int main(int argc, char** argv)
{
    try
    {
        string serviceRegistryAddressToSet;
        if(argc == 2)
        {
            serviceRegistryAddressToSet = argv[2];
        }
        else
        {
            serviceRegistryAddressToSet = "127.0.0.1:4000";
        }
        GetImage imageGetter(serviceRegistryAddressToSet);
        ByteArray receivedFile;
        imageGetter("inesistenteSulServer.jpg", receivedFile);
    }
    catch(const exception& e)
    {
        cout <<  e.what() << endl;
    }
    return 0;
}

