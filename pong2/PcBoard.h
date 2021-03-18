#pragma once

#include "Board.h"


class PcBoard : public Board {
public:
	enum levels { Best = 0, Good = 1, Novice = 2 };
private:

	levels PcState;
	Ball* BallPosition; //{BallPosition(&pong.getball()) 
	Point dest= Point(Ball::StartX,Ball:: StartY, ' ');

public:
	PcBoard(const Point& up1, const Point& down1, const BoardSide& side1, const levels& level1, Ball *ballpos) : Board(up1, down1, side1), PcState(level1), BallPosition(ballpos) {}
	void changeDir();
	void WinOrLose();
	void lose(const int &chance);

	void setLevel(const char &level)
	{
		PcState = levels(level-'a');
	}
	levels getLevel()
	{
		return PcState;
	}
	void findDest();


};