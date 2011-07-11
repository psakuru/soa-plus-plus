#include "../../ServiceOrientedArchitecture/Service/Stub/StreamStub/StreamStub.h"
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
#include <time.h>
#include "../GetImage.h"
#include "../StoreImage.h"
#include "../GetList.h"
#include "../RotateImage.h"
#include "../HorizontalFlipImage.h"
using namespace std;

int main(int argc, char** argv)
{
	try
	{
		if(argc < 1)
		{
			cout << "Necessita del parametro [nome_file_da_inviare].jpg";
			return 0;
		}
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
			cout << "Unable to open file.";
			return;
		}
		ByteArray fileBytes((void*)memblock, size);
		delete[] memblock;
		cout << "Richiedo il servizio StoreImage.";
		StoreImage p;
		p(argv[1], fileBytes);
		cout << "Richiedo la lista di immagini registrate.";
		GetList z;
		string lista;
		z(lista);
		boost::char_separator<char> separator(";");
		boost::tokenizer< boost::char_separator<char> > parser(lista,separator);
		cout << "LISTA: " << endl;
		BOOST_FOREACH(string entry, parser)
		{
			cout << entry <<endl;
		}
		vector<string> entries(parser.begin(), parser.end());
		// Scelgo a caso un'immagine da ricevere.
		srand( time(NULL) );
		int random = rand() % entries.size();
		string nameOfFileToReceive = entries[random];
		cout << "Richiedo un'immagine a caso fra quelle presenti sul server.";
		GetImage s;
		ByteArray fileRicevuto;
		s(nameOfFileToReceive, fileRicevuto);
		ofstream outfile (nameOfFileToReceive.c_str(),ofstream::binary | ofstream::out);
		outfile.write((char*)fileRicevuto.getPointer(),fileRicevuto.getLength());
		outfile.close();
		cout << "Immagine ricevuta e salvata: " << nameOfFileToReceive << endl;
		//Richiedo a caso il servizio di flip o quello di rotate sull'immagine appena ricevuta.
		random = rand() % 2;
		ByteArray fileDaRicevere;
		if (random == 0)
		{
			cout << "Richiedo il servizio di HorizontalFlip sull'immagine: " << nameOfFileToReceive << endl;
			HorizontalFlipImage hfi;
			hfi(fileRicevuto,fileDaRicevere);
			ofstream outfile (nameOfFileToReceive.c_str(),ofstream::binary | ofstream::out);
			outfile.write((char*)fileDaRicevere.getPointer(),fileDaRicevere.getLength());
			outfile.close();			
		}
		else
		{
			cout << "Richiedo il servizio di Rotate sull'immagine: " << nameOfFileToReceive;
			RotateImage ri;
			// L'angolo di rotazione viene scelto a caso.
			random = rand();
			cout << " di un angolo di " << random << " gradi." << endl;
			ri(random,fileRicevuto,fileDaRicevere);
			ofstream outfile (nameOfFileToReceive.c_str(),ofstream::binary | ofstream::out);
			outfile.write((char*)fileDaRicevere.getPointer(),fileDaRicevere.getLength());
			outfile.close();			
		}
		cout << "Richiedo il servizio di StoreImage sull'immagine modificata: " << nameOfFileToReceive << endl;
		StoreImage si;
		si(nameOfFileToReceive,fileDaRicevere);
    }
    catch(const exception& e)
	{
    	cout e.what() << endl;
	}
	return 0;
}

