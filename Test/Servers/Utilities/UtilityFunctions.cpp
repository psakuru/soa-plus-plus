#include "UtilityFunctions.h"

RawByteBuffer* loadImage(string name)
{
	char* memoryBlock;
	uint64_t size = 0;
	ifstream file(name.c_str(), ios::in | ios::binary | ios::ate);
	size = (int)file.tellg();
	memoryBlock = (char*)malloc(size);
	file.seekg(0, ios::beg); 
	file.read(memoryBlock, size); 
	file.close();
	ByteArray* fileBytes = new ByteArray((void*)memoryBlock, size);
	free(memoryBlock);
	RawByteBuffer* objectToBeSent = new RawByteBuffer(fileBytes, false);
	return objectToBeSent;
}

void storeImage(string name,ByteArray* bufferPointer)
{
	ofstream outfile (name.c_str(),ofstream::binary | ofstream::out);
	outfile.write( (char*)(bufferPointer->getPointer() ) , bufferPointer->getLength() );
	outfile.close();
}
