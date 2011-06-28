#include "RRFIFOMonitoredExtensibleMap.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	RRFIFOMonitoredExtensibleMap<string, string> m;
	m.insertElement("Primo", "1");
	m.insertElement("Secondo", "2");
	m.insertElement("Terzo", "3");
	m.insertElement("Primo", "11");
	m.insertElement("Primo", "111");
	m.insertElement("Terzo", "33");
	m.print();
	m.clearElement("Secondo", "2");
	m.print();
	m.clearElement("Primo", "11");
	m.insertElement("Primo", "1111");
	m.clearElement("Primo", "a");
	m.print();
	cout << m["Primo"] << endl;
	cout << m["Primo"] << endl;
	cout << m["Primo"] << endl;
	cout << m["Primo"] << endl;
	cout << m["Primo"] << endl;
	cout << m["Primo"] << endl;
	cout << m["Primo"] << endl;
	cout << m["Primo"] << endl;
	cout << m["Primo"] << endl;
	cout << m["Primo"] << endl;
	cout << m["Primo"] << endl;	
	return 0;
}
