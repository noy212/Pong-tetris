#include "PcBoard.h"


void PcBoard::changeDir()
{

	if (get_up().get_Y() > dest.get_Y())
		Board::changeDir(0, -1);
	else if (get_up().get_Y() < dest.get_Y())
		Board::changeDir(0, 1);
	else
		Board::changeDir(0, 0);


}

void PcBoard::findDest()
{
	dest.set_x(BallPosition->get_x());
	dest.set_y(BallPosition->get_y());
	int dirx = BallPosition->getXDir();
	int diry = BallPosition->getYDir();
	if (getSide() == Right && dirx == 1)
	{
		while (dest.get_X() < (get_up().get_X()) - 4) {

			if (dest.get_Y() == min_y  || dest.get_Y() +2== max_y )
				diry *= -1;
			dest.move(dirx, diry);
		}
	}
	else if (getSide() == Left && dirx == -1)
	{
		while (dest.get_X() > (get_up().get_X())+1) {

			if (dest.get_Y() == min_y || dest.get_Y()+2 == max_y )
				diry *= -1;
			dest.move(dirx, diry);
		}
	}

}

void PcBoard::WinOrLose() {

	findDest();
	if (PcState != Best)
		lose(rand() % 100);

}

void PcBoard::lose(const int &chance)
{

	if (PcState == Good&&chance>40)
	{
		if (dest.get_Y() - min_y > 4)
			dest.set_y(dest.get_Y() - 4);
		else
			dest.set_y(dest.get_Y() + 4);

	}
	else if (PcState == Novice&& chance > 10)
	{
		if (dest.get_Y() - min_y > 4)
			dest.set_y(dest.get_Y() - 4);
		else
			dest.set_y(dest.get_Y() + 4);

	}
	else if(PcState == Best)
	{
		if (dest.get_Y() - min_y > 4)
			dest.set_y(dest.get_Y() - 4);
		else
			dest.set_y(dest.get_Y() + 4);
	}

}
