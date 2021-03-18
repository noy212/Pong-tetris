#pragma once

#include "Board.h"
#include "KeyboardManager.h"


class UserBoard :public Board, public KeyEvents {
	string kbChars;
	unsigned char currChar = 0;

public:
	UserBoard(const Point& up1, const Point& down1, const BoardSide& side1, const string& keys1) : Board(up1, down1,side1), kbChars(keys1) {}

	const string getKbChars()
	{
		return kbChars;
	}

	void handleKey(const unsigned char &key);
	void changeDir();


	void lose(const int &chance)
	{
		return;
	}

	void WinOrLose()
	{
		return;
	}

};


