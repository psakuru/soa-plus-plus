#include "../SerializableObjects/SerializationStrategies/StringSerializationStrategy/StringSerializationStrategy.h"
#include "../SerializableObjects/SerializationStrategies/IntegerSerializationStrategy/IntegerSerializationStrategy.h"
#include <stdint.h>
#include <string>
using namespace std;

int main()
	{
	string ciao = "ciao";
	int c = 7;
	SerializableObject* i = new Integer(c);
	SerializableObject* s = new String(ciao);
	i=s;
	return 0;
	}
