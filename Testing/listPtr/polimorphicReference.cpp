#include <exception>
#include <iostream>
using namespace std;

class MyException : public exception
{
 virtual const char* what() const throw()
 {
 return "SONO IO";
 }
};

int main()
{
try{throw MyException();}
catch(const exception& prova)
{
cout << "colta nel catch:" << prova.what() << endl;
}
}
