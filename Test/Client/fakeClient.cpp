#include "../../ServiceOrientedArchitecture/Service/Stub/StreamStub/StreamStub.h"
#include <exception>
#include "GetImage.h"
#include <string>
using namespace std;

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
        s("inesistenteSulServer.jpg", receivedFile);
    }
    catch(const exception& e)
    {
        cout <<  e.what() << endl;
    }
    return 0;
}

