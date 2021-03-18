#pragma once
#include <map>
#include "BallBehavior.h"
#include "KeyEvents.h"

using namespace std;

class RegularBall : public BallBehavior, public KeyEvents {

	string kbChars = "sk";
	ballside bombSide = none;
	map<char, ballside> ballstateKeys;
	unsigned char currChar = 0;

public:

	RegularBall() 
	{
		ballstateKeys['s'] = left;
		ballstateKeys['k'] = right;
	}
	void resetBombSide() {
		bombSide = none;
	}
	void resetIteration() {
		return;
	}
	void setIteration() {
		return;
	}
	void resetCurrChar() {
		currChar = 0;
	}
	bool changeState() {
		if (bombSide != none && currChar != 0) {
			resetCurrChar();
			return true;
		}
		return false;
	}
	void handleKey(const unsigned char &key);
	const string getKbChars() {
		return kbChars;
	}

};