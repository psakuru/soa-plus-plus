#include "../ServiceOrientedArchitecture/Service/Stub/StreamStub/StreamStub.h"
#include <fstream>
#include <exception>
#include <errno.h>
#include <string.h>
#include <boost/tokenizer.hpp>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <boost/foreach.hpp>
#include <boost/token_functions.hpp>
#include "GetImage.h"
#include "StoreImage.h"
#include "GetList.h"
#include "RotateImage.h"
#include "HorizontalFlipImage.h"
using namespace std;

int main(int argc, char** argv)
{
	try
	{
		char * memblock;
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
		else 
		{
			cout << "Unable to open file";
		}
		ByteArray fileBytes((void*)memblock, size);
		delete[] memblock;
		StoreImage p;
		p(argv[1], fileBytes);
		GetList z;
		string lista;
		z(lista);
		boost::char_separator<char> separator("\\");
		boost::tokenizer<boost::char_separator<char>> parser(lista);
		cout << "LISTA: " << endl;
		BOOST_FOREACH(string entry, parser)
		{
			cout << entry << endl;
		}
		vector<string> entries(parser.begin(), parser.end());
		int random = rand() % entries.size();
		string nameOfFileToReceive = entries[random];
		GetImage s;
		ByteArray fileRicevuto;
		s(nameOfFileToReceive, fileRicevuto);
		ofstream outfile (nameOfFileToReceive.c_str(),ofstream::binary | ofstream::out);
		outfile.write((char*)fileRicevuto.getPointer(),fileRicevuto.getLength());
		outfile.close();
		cout << "FILE SALVATO: " << nameOfFileToReceive << endl;
		random = rand() % 2;
		ByteArray fileDaRicevere;
		if (random == 0)
		{
			HorizontalFlipImage hfi;
			hfi(fileRicevuto,fileDaRicevere);
			s(nameOfFileToReceive, fileDaRicevere);
			ofstream outfile (nameOfFileToReceive.c_str(),ofstream::binary | ofstream::out);
			outfile.write((char*)fileDaRicevere.getPointer(),fileDaRicevere.getLength());
			outfile.close();			
		}
		else
		{
			RotateImage ri;
			random = rand() % 361;
			ri(random,fileRicevuto,fileDaRicevere);
			s(nameOfFileToReceive, fileDaRicevere);
			ofstream outfile (nameOfFileToReceive.c_str(),ofstream::binary | ofstream::out);
			outfile.write((char*)fileDaRicevere.getPointer(),fileDaRicevere.getLength());
			outfile.close();			
		}
		StoreImage si;
		si(nameOfFileToReceive,fileDaRicevere);
	    cout << "fine." << endl;
    }
    catch(const exception& e)
	{
    	cout << "MUMBLE MUMBLE: " << e.what() << endl;
	}
    catch(...)
    {
        cout << "ARRIVA QUALCOSA" << endl;
    }
    return 0;
}

