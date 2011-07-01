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
            //cout << "BEGIN: ParticularServiceStreamStub()" << endl;
            //cout << "Passati i parametri di default al costruttore di StreamStub" << endl;
            //cout << "END ParticularServiceStreamStub()" << endl;
        }
    void operator()(int i, double d, string s, ByteArray& B, BadRequestSignal& b)
    {
        //cout << "BEGIN: ParticularServiceStreamStub.operator()" << endl;
        //cout << "Insersco un int" << endl;
        (*this) << i;
        //cout << "Inserisco un double nella lista di output" << endl;
        (*this) << d;
        //cout << "Inserisco una string nella lista di output" << endl;
        (*this) << s;
        //cout << "Inserisco un ByteArray nella lista di output" << endl;
        (*this) >> B;
        //cout << "Inserisco un BadRequestSignal nella lista di output" << endl;
        (*this) >> b;
        //cout << "Invoco il protocollo" << endl;
        bind();
        protocol();
        //cout << "END: ParticularServiceStreamStub.operator()" << endl;
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
                //cout << strerror(errno) << endl;
        memblock = new char [size];
                //cout << strerror(errno) << endl;
        file.seekg (0, ios::beg);
                //cout << strerror(errno) << endl;
        file.read (memblock, size);
                //cout << strerror(errno) << endl;
        file.close();
                //cout << strerror(errno) << endl;
        //cout << "the complete file content is in memory" << endl;
        //cout << "File size: " << size << endl;
        }
    else cout << "Unable to open file";
    //cout << "File caricato in memoria all' indirizzo " << hex << (void*)memblock << dec << endl;
    ByteArray fileBytes((void*)memblock, size);
    //p.staticallyBind("127.0.0.1:3000");
    BadRequestSignal b;
    ParticularServiceStreamStub p;
    p(43,2.4,"ciao",fileBytes, b);
    delete[] memblock;
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

