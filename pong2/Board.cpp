#include "Board.h"
#include "Screen.h"



void Board::draw(COLOR colorType)
{
	Point temp = up;
	setColor(colorType);
	temp.draw();
	while (temp != down) {
		temp.move(0, 1);
		temp.draw();
	}
}

void Board::erase()
{
	Point temp = up;
	setColor(COLOR::BLACK_BACKGROUND);
	temp.erase();
	while (temp != down) {
		temp.move(0, 1);
		temp.erase();
	}
}

void Board::moveBoard()
{

	changeDir();
	if (checkYLimit())
		return;
	if (dirx == 0 && diry == 0)
		return;
	if (diry==-1)
	{
		down.erase();
		down.move(dirx, diry);
		up.move(dirx, diry);
		setColor(COLOR::GREEN_BACKGROUND);
		up.draw();
	}
	else
	{
		up.erase();
		up.move(dirx, diry);
		down.move(dirx, diry);
		setColor(COLOR::GREEN_BACKGROUND);
		down.draw();
	}


}



bool Board::checkYLimit() const
{
	return (up.get_Y() == min_y&&diry==-1 || down.get_Y() == max_y&&diry == 1);
}

bool Board::checkXLimit() const
{
	return (up.get_X() == min_x || down.get_X() == max_x);
}


void Board::moveRL(const BoardSide &side)
{
	if (side == Left)
	{
		if (checkXLimit())
			return;
		this->erase();
		up.move(-1, 0);
		down.move(-1, 0);
		this->draw(COLOR::RED_BACKGROUND);
	}
	else if (side == Right)
	{
		if (checkXLimit())
			return;
		this->erase();
		up.move(1, 0);
		down.move(1, 0);
		this->draw(COLOR::RED_BACKGROUND);
	}
}


Board::HitBoard Board::checkHit(const Ball &b)
{
	int distance;
	if (side == Left)
		distance = b.get_x() - up.get_X();
	else
		distance = up.get_X() - b.get_x() - 3;
		if (distance < 1)
		return MISSED;
	if (distance > 1)
		return AWAY;

	if (b.get_y() >= up.get_Y() - 1 && b.get_y() <= down.get_Y() - 1)
		return CENTER;

	if ((b.get_y() == up.get_Y() - 2 && b.getYDir() == Ball::DOWN)
		|| (b.get_y() == down.get_Y() && b.getYDir() == Ball::UP)
		|| b.get_y() == up.get_Y() - 3 && b.getYDir() == Ball::DOWN)
		return CORNER;
	if (distance <= 1)
		return MISSED;
	return AWAY;

}


