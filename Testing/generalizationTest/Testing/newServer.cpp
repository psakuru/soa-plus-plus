#include <iostream>
#include <fstream>
#include <list>
#include <exception>
#include "../TcpIpSocket/TcpIpPassiveSocket.h"
#include "../SerializableObjects/SerializableObject.h"
#include "../SerializableObjects/DeserializationStrategies/SerializableObjectBuilder.h"
#include "../SerializableObjects/DeserializationStrategies/TerminalSerializableObjectBuilder.h"
#include "../SerializableObjects/Utilities/ByteArray/ByteArray.h"
#include "../SerializableObjects/SerializationStrategies/RawByteBufferSerializationStrategy/RawByteBufferSerializationStrategy.h"
#include "../SerializableObjects/SerializationStrategies/IntegerSerializationStrategy/IntegerSerializationStrategy.h"
#include "../SerializableObjects/SerializationStrategies/RealSerializationStrategy/RealSerializationStrategy.h"
#include "../SerializableObjects/SerializationStrategies/StringSerializationStrategy/StringSerializationStrategy.h"
#include "../SerializableObjects/SerializationStrategies/SignalSerializationStrategy/SignalSerializationStrategy.h"
#include "../SerializableObjects/DeserializationStrategies/SignalBuilder.h"
#include "../SerializableObjects/SerializationStrategies/SignalSerializationStrategy/SignalTypeConstants.h"
#include "../SerializableObjects/SerializationStrategies/SignalSerializationStrategy/ParticularSignals/BadRequestSerializationStrategy/BadRequestSerializationStrategy.h"
#include "../ServiceOrientedArchitecture/Service/Skeleton/Skeleton.h"
using namespace std;

class ParticularSkeleton : public Skeleton
{
    protected:
        void doService()
        {
        /* <ricezione e store> */
        SerializableObjectList::iterator i = inputParameters.begin();
        while((*i).getType() != SERIALIZABLE_RAW_BYTE_BUFFER) i++;
        SerializableObject* r = &(*i);
        ByteArray* pb = (ByteArray*)(r->getValue());
        ofstream outfile ("ricevutoDalClientIninput.jpg",ofstream::binary);
        outfile.write( (char*)( pb->getPointer() ) , pb->getLength() );
        delete pb;
        /* </ricezione e store> */
        char * memblock;
        uint64_t size = 0;
        ifstream file ("tux.jpg", ios::in|ios::binary|ios::ate);
        if (file.is_open())
            {
            size = (int)file.tellg();
            memblock = new char [size];
            file.seekg (0, ios::beg);
            file.read (memblock, size);
            file.close();
            cout << "the complete file content is in memory, filesize: " << size << endl;
            }
        else cout << "Unable to open file";
        ByteArray* fileBytes = new ByteArray((void*)memblock, size); //TODO Questo è un Memory Leak!
        RawByteBuffer* objectToSend = new RawByteBuffer(*fileBytes);
        BadRequest* badRequest = new BadRequest();
        outputParameters.push_back(objectToSend); //Tanto poi ci pensa la lista boost a fare la delete!
        outputParameters.push_back(badRequest);
        }
    public:
        ParticularSkeleton()
        {
            inputParameters.push_back(new Integer);
            inputParameters.push_back(new Real);
            inputParameters.push_back(new String);
            inputParameters.push_back(new RawByteBuffer);
            inputParameters.push_back(new BadRequest);
        }
        ParticularSkeleton(string ServiceID, int port, int backlog)
        : Skeleton(ServiceID, port, backlog)
        {
            inputParameters.push_back(new Integer);
            inputParameters.push_back(new Real);
            inputParameters.push_back(new String);
            inputParameters.push_back(new RawByteBuffer);
            inputParameters.push_back(new BadRequest);
        }
        void service()
        {
            bind();
        }
};



int main()
	{
    ParticularSkeleton pS("redHat(IN: int, double, string; INOUT: ByteArray, BadRequestSignal)", 4000, 5);
    pS.service();
	return 0;
	}

