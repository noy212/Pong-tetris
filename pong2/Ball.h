#pragma once
#include "Point.h"
#include "BallBehavior.h"


class Ball 
{
public:
	enum stateNameTypes { Regular, Becoming, Bomb };
private:
	Point position[4][3];
	int dir_x=1;
	int dir_y=1;
	BallBehavior* ballState;
	stateNameTypes stateName;
	COLOR ballcolor = COLOR::BLUE_TEXT;
public: 
	enum { StartX = 37, StartY = 14 };
	enum Ydirection { UP = -1, DOWN = 1 };
	enum Xdirection { Left = -1, Right = 1 };
	enum HIT { MISSED = 0, AWAY = 1, CENTER = 2, CORNER = 3 };
	Ball() : position{  { { StartX,StartY,' ' },{ StartX,StartY+1,'O' },{ StartX,StartY+2,' ' } } ,
						{ { StartX+1,StartY,'O' },{ StartX+1,StartY+1,'O' },{ StartX+1,StartY+2,'O' } } ,
						{ { StartX+2,StartY,'O' },{ StartX+2,StartY+1,'O' },{ StartX+2,StartY+2,'O' } } ,
						{ { StartX+3,StartY,' ' },{ StartX+3,StartY+1,'O' },{ StartX+3,StartY+2,' ' } } }
	{ resetBall(); }

	void setBehavior(BallBehavior* newState, const stateNameTypes& newstateName) {
		stateName = newstateName;
		ballState = newState;
		if(newstateName == Regular)
			setBallColor(COLOR::BLUE_TEXT);
		else if (newstateName == Becoming)
			setBallColor(COLOR::GRAY_TEXT);
		else if (newstateName == Bomb)
			setBallColor(COLOR::RED_TEXT);
	}
	stateNameTypes getStateName() {
		return stateName;
	}
	BallBehavior* getBehavior() {
		return ballState;
	}
	void setBallColor(COLOR colorName) {
		ballcolor = colorName;
	}
	void resetBall();
	void move();
	void draw();
	void eraseBall();

	const int &get_y() const
	{
		return position[0][0].get_Y();
	}
	const int &get_x() const
	{
		return position[0][0].get_X();
	}

	void changeYdir()
	{
		dir_y *= -1;
	}
	void changeXdir()
	{
		dir_x *= -1;
	}

	Ydirection getYDir() const
	{
		return dir_y == 1 ? DOWN : UP;
	}
	const Xdirection &getXDir() const
	{
		return dir_x == 1 ? Right : Left;
	}

	void start_new_ball() 
	{
		eraseBall();
		resetBall();
		draw();

	}
	void moveY(const int &y);
	void animate(const HIT &hit, const int &side);
	void Lanimate(const int &y);
	void Ranimate(const int &y);

};