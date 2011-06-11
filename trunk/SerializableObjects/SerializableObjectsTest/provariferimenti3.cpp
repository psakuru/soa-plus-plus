#include <iostream>
#include <string>
#include <list>
#include <boost/ref.hpp>
#include "String.h"
using namespace std;

typedef boost::reference_wrapper<string> stringReference;

class ServiceProxy
	{
	private:
		list<SerializableObject*> parametersIN;
		list<SerializableObject*> parametersOUT;
	protected:
		friend ServiceProxy& operator>>(ServiceProxy& proxy, string& parameter);
		friend ServiceProxy& operator<<(ServiceProxy& proxy, string& parameter);
		void sendRequest();
	};

void ServiceProxy::sendRequest()
	{
	list<SerializableObject*>::iterator i = parametersOUT.begin();
	list<SerializableObject*>::iterator j = parametersIN.begin();
	void* stringaSerializzata;
	(*j)->serialize(stringaSerializzata);
	SerializableObject* ritorno = new String();
	ritorno->deserialize(stringaSerializzata);
	*(*i) = *(*j);
	return;
	}

ServiceProxy& operator>>(ServiceProxy& proxy, string& parameter)
	{
	SerializableObject* s = new String(parameter);
	proxy.parametersOUT.push_back(s);
	return proxy;
	}

ServiceProxy& operator<<(ServiceProxy& proxy, string& parameter)
	{
	SerializableObject* s = new String(parameter);
	proxy.parametersIN.push_back(s);
	return proxy;
	}

class ParticularServiceProxy : public ServiceProxy
	{
	public:
		void operator()(string& parameter1, string parameter2);
	};

void ParticularServiceProxy::operator()(string& parameter1, string parameter2)
	{
	(*this) >> parameter1 << parameter2;
	sendRequest();
	return;
	}

int main()
	{
	string serviceIs = "ServiceIs";
	string reliable = "Reliable";
	ParticularServiceProxy proxy;
	proxy(serviceIs, reliable);
	cout << "Dopo un viaggio fantastico, la mia variabile locale vale: " <<  serviceIs << endl;
	return 0;
	}
