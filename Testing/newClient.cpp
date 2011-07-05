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
    void operator()(int i, double d, string s, ByteArray& B, BadRequestSignal& b)
    {


        (*this) << i;

        (*this) << d;

        (*this) << s;

        (*this) >> B;

        (*this) >> b;

        bind();
        protocol();

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
    BadRequestSignal b;
    ParticularServiceStreamStub p;
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

