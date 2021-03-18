
#include "UserBoard.h"

void UserBoard::handleKey(const unsigned char &key)
{
	currChar = key;
}

void UserBoard::changeDir() {
	if (currChar == 0) {
		setDirx(0);
		setDiry(0);
		return;
	}
	if (currChar == kbChars[UP]) {
		Board::changeDir(0,-1);
	}
	else  if (currChar == kbChars[DOWN]) {
		Board::changeDir(0,1);
	}
	currChar = 0;
}