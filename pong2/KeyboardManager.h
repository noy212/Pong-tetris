#pragma once

#include <list>
#include "Board.h"
#include "KeyEvents.h"

class KeyboardManager 
{
	enum { NUM_CHARS = 26};
	list<KeyEvents*> Kblist[NUM_CHARS];
	
	int getIndex(const char &c) 
	{
		int index = c - 'a';
		if (index < 0 || index >= NUM_CHARS)
			return -1;
		return index;
	}

public:
	void addtoKbList(KeyEvents* pEvent);
	bool handleKeyboard();
};
