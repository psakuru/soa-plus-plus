#include "../ServiceOrientedArchitecture/Service/Stub/StreamStub/StreamStub.h"
#include <fstream>
#include <exception>
#include <errno.h>
#include <string.h>
#include <iostream>
using namespace std;

class ParticularServiceStreamStub : public StreamStub
{
public:
    ParticularServiceStreamStub()
        : StreamStub("redHat", "127.0.0.1:4000")
        {



        }
    void operator()(int i, double d, string s, ByteArray& B, GenericSignalValue& b)
    {
    	cout << "Dimensione input iniziale: " << (int)inputParameters.size() << endl;
    	cout << "Dimensione output iniziale: " << (int)outputParameters.size() << endl;
        (*this) << i;

        (*this) << d;

        (*this) << s;

        (*this) >> B;

        (*this) >> b;
        remoteProcedureCall();
        //ATTENZIONEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE:
        cout << "Dimensione input finale: " << (int)inputParameters.size() << endl;
        cout << "Dimensione output finale: " << (int)outputParameters.size() << endl;
    }
};

int main()
	{
	try{
	char * memblock;
//    ifstream::pos_type size;
	uint64_t size = 0;
    ifstream file ("daInviareAlServer.jpg", ios::in|ios::binary|ios::ate);
    if (file.is_open())
        {
        size = file.tellg();

        memblock = new char [size];

        file.seekg (0, ios::beg);

        file.read (memblock, size);

        file.close();



        }
    else cout << "Unable to open file";

    ByteArray fileBytes((void*)memblock, size);
    delete[] memblock;
    //p.staticallyBind("127.0.0.1:3000");
    GenericSignalValue b;
    ParticularServiceStreamStub p;
    p(43,2.4,"ciao",fileBytes, b);
    p(43,2.4,"ciao",fileBytes, b);
    p(43,2.4,"ciao",fileBytes, b);
    ofstream outfile ("ricevutoDalServer.jpg",ofstream::binary | ofstream::out);
    outfile.write((char*)fileBytes.getPointer(),fileBytes.getLength());
    outfile.close();
    }
    catch(const exception& e)
    	{
    	cout << e.what() << endl;
    	}
    catch(...)
    {
        cout << "ARRIVA QUALCOSA" << endl;
    }
    return 0;
    }

