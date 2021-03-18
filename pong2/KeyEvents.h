#pragma once


#include <string>
using namespace std;

struct KeyEvents
{
	virtual void handleKey(const unsigned char &key) = 0;
	virtual const string getKbChars() = 0;
};
