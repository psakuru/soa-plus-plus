#include "../ServiceOrientedArchitecture/ServiceProxy/ServiceProxy.h"
#include <fstream>
#include <iostream>
#include <exception>
#include <errno.h>
#include <string.h>
using namespace std;

class ParticularServiceProxy : public ServiceProxy
	{
	public:
		void operator()(int i, double d, string s, ByteArray& b)
			{
			(*this) << i;
			(*this) << d;
			(*this) << s;
			(*this) >> b;
			doService();
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
                cout << strerror(errno) << endl;
        memblock = new char [size];
                cout << strerror(errno) << endl;
        file.seekg (0, ios::beg);
                cout << strerror(errno) << endl;
        file.read (memblock, size);
                cout << strerror(errno) << endl;
        file.close();
                cout << strerror(errno) << endl;
        cout << "the complete file content is in memory" << endl;
        cout << "File size: " << size << endl;
        }
    else cout << "Unable to open file";
    cout << "File caricato in memoria all' indirizzo " << hex << (void*)memblock << dec << endl;
    ByteArray fileBytes((void*)memblock, size);
    ParticularServiceProxy p;
    p.staticallyBindProxy("127.0.0.1:4000");
    p(43,2.4,"ciao",fileBytes);
    ofstream outfile ("ricevutoDalServer.jpg",ofstream::binary);
    outfile.write((char*)fileBytes.getPointer(),fileBytes.getLength());}
    catch(exception& e)
    	{
    	cout << e.what() << endl;
    	}
    catch(...)
    	{
    	cout << "Eccezione ignota" << endl;
    	}
    return 0;
    }
