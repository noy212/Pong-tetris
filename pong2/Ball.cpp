#include "Ball.h"
#include "Screen.h"


void Ball::move()
{
	int i, j;
	if (Screen::checkXLimit(position[0][0]) || Screen::checkXLimit(position[3][0]))
		dir_x *= -1;
	if (Screen::checkYLimit(position[0][0]) || Screen::checkYLimit(position[0][2]))
		dir_y *= -1;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 3; j++)
		{
			position[i][j].erase();
			position[i][j].move(dir_x, dir_y);
		}
	}
	draw();
}

void Ball::moveY(const int &y)
{
	{
		int i, j;
		if (Screen::checkYLimit(position[0][0]) || Screen::checkYLimit(position[0][2]))
			dir_y *= -1;

		eraseBall();
		for (i = 0; i < 4; i++)
			for (j = 0; j < 3; j++)
				position[i][j].move(0, y);

		draw();
	}
}

void Ball::draw()
{
	int i = 0, j = 0;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 3; j++) {
			if (position[i][j].get_char() == ' ')
				setColor(COLOR::BLACK_BACKGROUND);
			else
				setColor(ballcolor);
			position[i][j].draw();
		}
	}
}

void Ball::eraseBall()
{
	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 3; j++)
		{
			position[i][j].erase();
		}
}

void Ball::resetBall()
{
	//reset ball position and direction
	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 3; j++)
		{
			if (j == 0 && (i == 0 || i == 3) || j == 2 && (i == 0 || i == 3))
				position[i][j] = { StartX + i,StartY + j,' ' };
			else
				position[i][j] = { StartX + i,StartY + j,'O' };
		}
	dir_x = 1 - 2 * (rand() % 2);
	dir_y = 1 - 2 * (rand() % 2);
}




void Ball::animate(const HIT &hit, const int &side)
{

	if (side == Left)
	{
		if (hit == CENTER)
			Lanimate(dir_y);
		else if (hit == CORNER)
			Lanimate(dir_y*-1);
	}
	else
	{
		if (hit == CENTER)
			Ranimate(dir_y);
		else if (hit == CORNER)
			Ranimate(dir_y*-1);
	}
}

	void Ball::Lanimate(const int &y)
	{

		Sleep(70);
		if (y != dir_y)
			moveY(y);

		position[0][0].draw('O');
		position[0][2].draw('O');

		position[1][1 - y].erase();
		position[2][0].erase();
		position[2][2].erase();
		position[3][1].erase();

		Sleep(70);

		if (y == dir_y)
			moveY(y);


		position[0][1 - y].draw('O');
		position[2][1 - y].erase();

		Sleep(70);

		move();

	}

	void Ball::Ranimate(const int &y)
	{


		Sleep(70);
		if (y != dir_y)
			moveY(y);

		position[3][0].draw('O');
		position[3][2].draw('O');

		position[0][1].erase();
		position[1][0].erase();
		position[1][2].erase();
		position[2][1 - y].erase();


		Sleep(70);

		if (y == dir_y)
			moveY(y);

		position[3][1 - y].draw('O');
		position[1][1 - y].erase();

		Sleep(70);

		move();

	}
	

	