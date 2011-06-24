#include "../../ServiceOrientedArchitecture/Publisher/Publisher.h"
#include "../../ObjectInterfaces/RegistrableObject/RegistrableObject.h"
#include <iostream>
#include <string>
using namespace std;

class A
{};

class B : public A, public RegistrableObject
{
public:
string getRegistrationInfo(){return "quaqquaraqqua!";}
};

int main()
{
Publisher p("127.0.0.1");
RegistrableObject* test = new B();
p.addObjectToPublish(test);
return 0;
}
