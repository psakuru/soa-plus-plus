#include <iostream>
#include <string>
#include <typeinfo>
using namespace std;

class RegObj
{
public:
virtual void reg() = 0;
};

class CalObj
{
public:
virtual void operator()() = 0;
};

class Serv
{
protected:
string serviceID;
public:
Serv(){}
Serv(string ID) : serviceID(ID){cout << "Serv(string), serviceID settato: " << serviceID << endl;}
};

class Skel : public Serv
{
public:
Skel(){}
Skel(string ID) : Serv(ID){cout << "Skel(string), serviceID settato alla base: " << serviceID << endl;}
};

class RegSkel : public RegObj, virtual public Skel
{
public:
RegSkel(){}
RegSkel(string ID) : Skel(ID){cout << "RegSkel(string), serviceID settato alla base: " << serviceID << endl;}
void reg(){cout << "RegSkel::reg()" << endl;}
};

template <typename T> class CalServ : public CalObj, virtual public Skel
{
public:
CalServ(){}
CalServ(string ID) : T(ID){cout << "CalServ<"<< (typeid(T)).name() << ">(string), serviceID settato alla base: " << serviceID << endl;}
void operator()()=0;
};

class RegCalSkel : public RegSkel, public CalServ<Skel>
{
public:
RegCalSkel(){}
RegCalSkel(string ID) : Skel(ID), RegSkel(ID), CalServ<Skel>(ID)
	{
	cout << "RegCalSkel(string), serviceID settato alla base: " << serviceID << endl;
	}
void operator()(){cout << "RegCalSkel::operator()" << endl;}
};

class PartRegCalSkel : public RegCalSkel
{
public:
PartRegCalSkel() : Skel("Bertinotti"), RegCalSkel("Bertinotti") {}
};

int main()
{
PartRegCalSkel r;
return 0;
}
