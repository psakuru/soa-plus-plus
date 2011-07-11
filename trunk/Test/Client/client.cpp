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
#include "GetImage.h"
#include "StoreImage.h"
#include "GetList.h"
#include "RotateImage.h"
#include "HorizontalFlipImage.h"
#include "../../Utilities/ColorPrint/ColorPrint.h"
using namespace std;

vector<string> tokenize(string imageList)
{
    boost::char_separator<char> separator(";");
    boost::tokenizer< boost::char_separator<char> > parser(imageList, separator);
    cout <<  "<Image list>: " << endl;
    BOOST_FOREACH(string entry, parser)
    {
        cout << entry <<endl;
    }
    vector<string> entries(parser.begin(), parser.end());
    return entries;
}

int main(int argc, char** argv)
{
    try
    {
        string serviceRegistryAddressToSet;
        if(argc < 2)
        {
            cout << "Usage: client <filename.jpg> [registerIP:registerPort]";
            return 0;
        }
        if(argc == 3)
        {
            serviceRegistryAddressToSet = argv[2];
        }
        else
        {
            cout << RED_TXT << "Default registry: 127.0.0.1:4000" << DEFAULT << endl;
            serviceRegistryAddressToSet = "127.0.0.1:4000";
        }
        char* memoryBlock;
        uint64_t size = 0;
        ifstream file(argv[1], ios::in|ios::binary|ios::ate);
        if (file.is_open())
        {
            size = file.tellg();
            memoryBlock = new char [size];
            file.seekg (0, ios::beg);
            file.read(memoryBlock, size);
            file.close();
        }
        else
        {
            cout << "Unable to open file." << endl;
            return 1;
        }
        ByteArray fileBytes((void*)memoryBlock, size);
        delete[] memoryBlock;
        cout << GREEN_TXT << "StoreImage(" << argv[1] << ")" << DEFAULT << endl;
        StoreImage imageStorer(serviceRegistryAddressToSet);
        imageStorer(argv[1], fileBytes);
        cout << YELLOW_TXT << "GetList()" << DEFAULT << endl;
        GetList remoteLs(serviceRegistryAddressToSet);
        string imageList;
        remoteLs(imageList);
        vector<string> entries = tokenize(imageList);
        // Scelgo a caso un'immagine da ricevere.
        srand(time(0));
        int random = rand() % entries.size();
        string nameOfFileToReceive = entries[random];
        cout << BLUE_TXT << "GetImage(" << nameOfFileToReceive << ")" << DEFAULT << endl;
        GetImage imageBroker(serviceRegistryAddressToSet);
        ByteArray receivedFile;
        imageBroker(nameOfFileToReceive, receivedFile);
        ofstream outfile(nameOfFileToReceive.c_str(), ofstream::binary | ofstream::out);
        outfile.write((char*)receivedFile.getPointer(), receivedFile.getLength());
        outfile.close();
        cout << "Immagine ricevuta e salvata: " << nameOfFileToReceive << endl;
        //Richiedo a caso il servizio di flip o quello di rotate sull'immagine appena ricevuta.
        srand(time(0));
        random = rand() % 2;
        ByteArray filToReceive;
        if(random == 0)
        {
            cout << RED_TXT << "HorizontalFlip(" << nameOfFileToReceive << ")" << DEFAULT << endl;
            HorizontalFlipImage imageFlipper(serviceRegistryAddressToSet);
            imageFlipper(receivedFile,filToReceive);
            ofstream outfile(nameOfFileToReceive.c_str(), ofstream::binary | ofstream::out);
            outfile.write((char*)filToReceive.getPointer(),filToReceive.getLength());
            outfile.close();
        }
        else
        {
            RotateImage imageRotator(serviceRegistryAddressToSet);
            // L'angolo di rotazione viene scelto a caso.
            srand(time(0));
            random = rand() % 360;
            cout << RED_TXT << "RotateImage(" << random << "," <<  nameOfFileToReceive << ")" << DEFAULT << endl;
            imageRotator(random,receivedFile,filToReceive);
            ofstream outfile(nameOfFileToReceive.c_str(), ofstream::binary | ofstream::out);
            outfile.write((char*)filToReceive.getPointer(), filToReceive.getLength());
            outfile.close();
        }
        cout << GREEN_TXT << "StoreImage(" << nameOfFileToReceive << ")" << DEFAULT << endl;
        imageStorer(nameOfFileToReceive,filToReceive);
    }
    catch(const exception& e)
    {
        cout <<  e.what() << endl;
    }
    return 0;
}

