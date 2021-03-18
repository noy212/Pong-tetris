#pragma once
#include <string>
#include "Ball.h"

using namespace std;

class Board 
{
public:
	enum BoardSide { Left, Right };
	enum boarrdLimit { min_x = 1, max_x = 79, min_y = 4, max_y = 24 };
	enum HitBoard { MISSED, AWAY, CENTER, CORNER };
	enum moveDir { UP, DOWN };

private:

	Point up, down;
	BoardSide side;
	int dirx=0;
	int diry=0;

public:
	Board(const Point& up1, const Point& down1,const BoardSide& side1) : up(up1), down(down1), side(side1){}
	virtual ~Board(){}


	const BoardSide &getSide()
	{
		return side;
	}

	void draw(COLOR colorType);
	void erase();

	bool checkYLimit() const;
	bool checkXLimit() const;

	virtual void changeDir() = 0;

	virtual void WinOrLose() = 0;
	virtual void lose(const int &chance) = 0;

	void changeDir(const int &x, const int &y) {
		dirx = x;
		diry = y;
	}

	void setDirx(const int &x)
	{
		dirx=x;
	}
	void setDiry(const int &y)
	{
		diry=y;
	}
	void moveBoard();
	void moveRL(const BoardSide &side);

	const Point &get_up() const 
	{
		return up;
	}
	const Point &get_down() const 
	{
		return down;
	}
	void setXBoard(const int &new_x) 
	{
		up.set_x(up.get_X() + new_x);
		down.set_x(down.get_X() + new_x);
	}

	void reset_player(int x, int up_y, int down_y) 
	{
		up.set_x(x);
		down.set_x(x);
		up.set_y(up_y);
		down.set_y(down_y);
		
	}
	HitBoard checkHit(const Ball &b);


};