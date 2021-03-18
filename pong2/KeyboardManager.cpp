#include <conio.h>
#include "KeyboardManager.h"


void KeyboardManager::addtoKbList(KeyEvents* pEvent) {
	const string chars = pEvent->getKbChars();
	size_t numkeys = chars.length();
	for (size_t i = 0; i < numkeys; ++i) {
		int index = getIndex(chars[i]);
		if (index != -1)
			Kblist[index].push_back(pEvent);
	}
}



bool KeyboardManager::handleKeyboard()
{
	if (_kbhit()) 
	{
		unsigned char original = _getch();
		unsigned char key = tolower(original);
		if (original == '\x1b')
			return false;
		int index = getIndex(key);
		if (index != -1)
		{
			for (auto pEvent : Kblist[index])
			{
				if(pEvent!=nullptr)
					pEvent->handleKey(key);
			}
		}
	}
	return true;
}
