#include "../ServiceOrientedArchitecture/Service/Stub/StreamStub/StreamStub.h"
#include <fstream>
#include <exception>
#include <errno.h>
#include <string.h>
#include <iostream>
#include "GetImage.h"
#include "StoreImage.h"
#include "GetList.h"
using namespace std;

int main()
	{
	try{
	char * memblock;
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
   	StoreImage p;
    //ByteArray fileRicevuto;
    p("prova.jpg", fileBytes);
    //ofstream outfile ("ruotataDalServer.jpg",ofstream::binary | ofstream::out);
    //outfile.write((char*)fileRicevuto.getPointer(),fileRicevuto.getLength());
    //outfile.close();
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

