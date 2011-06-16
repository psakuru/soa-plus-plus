#ifndef CONTA_TAB_H
#define CONTA_TAB_H

#include <string>
using namespace std;

static int tabs = 0;

string tab()
	{
	string tablature;
	for(int i = 0; i < tabs; i++) tablature.append(" ");
	return tablature;
	}

#endif //CONTA_TAB_H
