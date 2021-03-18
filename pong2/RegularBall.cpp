#include "RegularBall.h"



void RegularBall::handleKey(const unsigned char & key)
{
	currChar = key;
	bombSide = ballstateKeys[key];
	if (bombSide == right)
		rightBombStatus = true;
	else
		leftBombStatus = true;
	player = bombSide;
}

