#include "../ServiceOrientedArchitecture/Service/Stub/StreamStub/StreamStub.h"
#include <fstream>
#include <exception>
#include <errno.h>
#include <string.h>
#include <iostream>
#include "HorizontalFlipImage.h"
using namespace std;

int main(int argc, char** argv)
{
	if(argc < 1)
	{
		cout << "Necessita del parametro [file].jpg";
		return 0;
	}	
	try{
	char * memblock;
//    ifstream::pos_type size;
	uint64_t size = 0;
    ifstream file (argv[1], ios::in|ios::binary|ios::ate);
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
    HorizontalFlipImage p;
    ByteArray fileRicevuto;
    p(fileBytes, fileRicevuto);
    ofstream outfile ("ricevutoDalServer.jpg",ofstream::binary | ofstream::out);
    outfile.write((char*)fileRicevuto.getPointer(),fileRicevuto.getLength());
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

