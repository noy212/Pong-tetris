#include "Screen.h"

bool Screen::checkFreePosition(const int &x_up, const int &y_up, const Board::BoardSide &side) const
{
	int data = 0;
	for (int i = 0; i < 3; ++i) 
	{
		if (side == Board::Right)
			data = (this->BoardPosition[x_up + 1][y_up + i]);
		else
			data = (this->BoardPosition[x_up - 1][y_up + i]);
		if (data == 1)
			return false;
	}
	return true;
}

void Screen::updateBoardPosition(Board& originalPlayer, Board &deadPlayer) 
{
	// while there is free place to the dead board and this is not the end screen - move and draw
	Board::BoardSide side = originalPlayer.getSide();
	while (checkFreePosition(deadPlayer.get_up().get_X(), deadPlayer.get_up().get_Y(), side) && !deadPlayer.checkXLimit())
	{
		freeBoardPosition(deadPlayer.get_up().get_X(), deadPlayer.get_up().get_Y());
		deadPlayer.moveRL(deadPlayer.getSide());
		updateBoardValues(deadPlayer.get_up().get_X(), deadPlayer.get_up().get_Y());
		Sleep(50);
	}
	if (checkFullLine(deadPlayer.get_up().get_X(), deadPlayer))
	{
		eraseLine(deadPlayer.get_up().get_X());
		moveDeadBoards(originalPlayer.get_up().get_X(), deadPlayer.get_up().get_X(), side);
		if (side == Board::Left)
			originalPlayer.setXBoard(-5);
		else
			originalPlayer.setXBoard(5);
	}

}




void Screen::freeBoardPosition(const int &x, const int &y) 
{	
	// point up values
	for (int i = 0; i < 3; ++i) 
		this->BoardPosition[x][y + i] = 0;
}

void Screen::updateBoardValues(const int &x, const int &y) 
{
	// point up values
	for (int i = 0; i < 3; ++i) 
		this->BoardPosition[x][y + i] = 1;
}

void Screen::eraseLine(const int &x) {
	Point pointToErase(x, 0, ' ');
	for (int y = Board::min_y; y <= Board::max_y; y++) {
		pointToErase.set_y(y);
		BoardPosition[x][y] = 0;
		pointToErase.erase();
	}
}

bool Screen::checkFullLine(int x, const Board &player) {
	for (int y = Board::min_y; y <= Board::max_y; y++) {
		if (BoardPosition[x][y] == 0)
			return false;
	}
	return true;

}
bool Screen::emptyLine(int x) {
	for (int y = Board::min_y; y <= Board::max_y; y++) {
		if (BoardPosition[x][y] == 1)
			return false;
	}
	return true;

}

void Screen::drawDeadBoard() 
{
	int i, j;
	Point pointToDraw(0, 0, ' ');
	for (i = Board::min_x; i <= Board::max_x; ++i) 
	{
		pointToDraw.set_x(i);
		for (j = Board::min_y; j <= Board::max_y; j++) 
		{
			pointToDraw.set_y(j);
			if (BoardPosition[i][j] == 0) {
				setColor(COLOR::BLACK_BACKGROUND);
				pointToDraw.set_char(' ');
			}
			else {
				setColor(COLOR::RED_BACKGROUND);
				pointToDraw.set_char('#');
			}
			pointToDraw.draw();
		}
	}
}

void Screen::drawScreen()
{
	int x, y;

	setColor(COLOR::GRAY_TEXT);
	gotoxy(37, 2);
	cout << "0 - 0";
	setColor(COLOR::TEAL_FADE_TEXT);
	

	for (x = Board::min_x; x <= Board::max_x; x++)
	{
		gotoxy(x, Board::min_y - 1);
		cout << '-';
		gotoxy(x, Board::max_y + 1);
		cout << '-';
	}
	for (y = Board::min_y; y <= Board::max_y; y++)
	{
		gotoxy(Board::min_x - 1, y);
		cout << '|';
		gotoxy(Board::max_x + 1, y);
		cout << '|';
	}
}

void Screen::freeAllBoard()
{
	int i, j;
	for (i = Board::min_x; i <= Board::max_x; i++) {
		for (j = Board::min_y; j <= Board::max_y; j++) {
			BoardPosition[i][j] = 0;
		}
	}
}




void Screen::moveDeadBoards(const int &max_x, const int &ereasedLine, const Board::BoardSide &side)
{
	int i, j;
	Point pointToDraw(0, 0, ' ');
	if (side == Board::Left) 
	{
		for (i = ereasedLine+1; i <= max_x; ++i) {
			for (j = Board::min_y; j <= Board::max_y; ++j) {
				BoardPosition[i - 1][j] = BoardPosition[i][j];
				if (BoardPosition[i][j] == 0) {
					setColor(COLOR::BLACK_BACKGROUND);
					pointToDraw.set_char(' ');
				}
				else {
					setColor(COLOR::RED_BACKGROUND);
					pointToDraw.set_char('#');
				}
				pointToDraw.set_x(i - 1);
				pointToDraw.set_y(j);
				pointToDraw.draw();
			}
		}
	}
	else {
		for (i = ereasedLine-1; i >= max_x; --i) {
			for (j = Board::min_y; j <= Board::max_y; ++j) {
				BoardPosition[i + 1][j] = BoardPosition[i][j];
				if (BoardPosition[i][j] == 0) {
					setColor(COLOR::BLACK_BACKGROUND);
					pointToDraw.set_char(' ');
				}
				else {
					setColor(COLOR::RED_BACKGROUND);
					pointToDraw.set_char('#');
				}
				pointToDraw.set_x(i + 1);
				pointToDraw.set_y(j);
				pointToDraw.draw();
			}
		}
	}

}



bool Screen::missedBoard(Ball *ball, Board *left_player, Board *right_player)
{
	Board::BoardSide side;
	int playerPos;
	int ball_x = ball->get_x();
	int ball_y = ball->get_y();
	if (ball_x > 40)
	{
		side = Board::BoardSide::Right;
		playerPos = right_player->get_up().get_X();
		ball_x += 4;

	}
	else
	{
		side = Board::BoardSide::Left;
		playerPos = left_player->get_up().get_X();
		ball_x -= 1;
	}
	int LineToerase = hitDead(ball, side);
	if (ball->getStateName() == Ball::stateNameTypes::Becoming)
	{
		if (ball_x-1 == Board::max_x || ball_x+1 == Board::min_x || (LineToerase != -1))
		{
			ball->eraseBall();
			return true; //it's a miss
		}
		return false;
	}
	if (ball_x - 1 == Board::max_x || ball_x + 1 == Board::min_x) //bombHitEdge
		bombHitEdge(side, playerPos, *left_player, *right_player, *ball);
	else if (LineToerase != -1) //bombHitDead
		bombHitDead(side, playerPos, *left_player, *right_player, *ball, LineToerase);
	right_player->draw(COLOR::GREEN_BACKGROUND);
	left_player->draw(COLOR::GREEN_BACKGROUND);
	return false;
	
}

void Screen::bombHitDead(Board::BoardSide side, int playerPos, Board& left_player, Board& right_player, Ball& ball,const int& LineToerase) {
	if (side == Board::BoardSide::Right)
	{
		eraseLine(LineToerase);
		moveDeadBoards(playerPos, LineToerase, side);

		right_player.moveRL(Board::BoardSide::Right);
		right_player.draw(COLOR::GREEN_BACKGROUND);

	}
	else
	{
		eraseLine(LineToerase);
		moveDeadBoards(playerPos, LineToerase, side);
		left_player.moveRL(Board::BoardSide::Left);
		left_player.draw(COLOR::GREEN_BACKGROUND);
	}
	ball.eraseBall();
	ball.resetBall();
	if (side == Board::Left&&ball.getXDir() != 1 || side == Board::Right&&ball.getXDir() != -1)
		ball.changeXdir();

	left_player.WinOrLose();
	right_player.WinOrLose();
}

void Screen::bombHitEdge(Board::BoardSide side, int playerPos, Board& left_player, Board& right_player, Ball& ball) {
	if (side == Board::BoardSide::Left)
	{
		if (!emptyLine(Board::min_x))
		{
			eraseLine(Board::min_x);
			moveDeadBoards(playerPos, Board::min_x, side);
			left_player.moveRL(Board::BoardSide::Left);
			left_player.draw(COLOR::GREEN_BACKGROUND);
		}

	}
	else
		if (!emptyLine(Board::max_x))
		{
			eraseLine(Board::max_x);
			moveDeadBoards(playerPos, Board::max_x, side);
			right_player.moveRL(Board::BoardSide::Right);
			right_player.draw(COLOR::GREEN_BACKGROUND);
		}
	ball.eraseBall();
	ball.resetBall();

	if (side == Board::Left && ball.getXDir() != 1 || side == Board::Right && ball.getXDir() != -1)
		ball.changeXdir();

	left_player.WinOrLose();
	right_player.WinOrLose();
}


int Screen::hitDead(Ball *ball, Board::BoardSide side)
{
	int startxB;
	int startyB;
	int maxxB;
	int maxyB;
	if (side == Board::BoardSide::Left) {
		startxB = ball->get_x() - 1;
		startyB = ball->get_y() - 1;
		maxxB = startxB + 2;
		maxyB = startyB + 4;
	}
	else {
		startxB = ball->get_x() +2;
		startyB = ball->get_y() - 1;
		maxxB = startxB + 2;
		maxyB = startyB + 4;
	}
	for (int i= startxB; i <= maxxB; i++) {
		for (int j= startyB; j <= maxyB; j++) {
			if (BoardPosition[i][j] == 1)
				return i;
		}
	}

	return -1;
	
	
	
	/*
	int x = ball->get_x();
	int y = ball->get_y();
	if (side == Board::BoardSide::Left) {
		if (BoardPosition[x - 1][y] == 1 || BoardPosition[x - 1][y + 1] == 1 || BoardPosition[x - 1][y + 2] == 1)
			return true;// center
		if (BoardPosition[x][y] == 1 || BoardPosition[x][y + 2] == 1 || BoardPosition[x][y + 3] == 1 || BoardPosition[x][y -1] == 1)
			return true; //corner
	}

	if (b.get_y() >= up.get_Y() - 1 && b.get_y() <= down.get_Y() - 1)
		return CENTER;

	if ((b.get_y() == up.get_Y() - 2 && b.getYDir() == Ball::DOWN)
		|| (b.get_y() == down.get_Y() && b.getYDir() == Ball::UP)
		|| b.get_y() == up.get_Y() - 3 && b.getYDir() == Ball::DOWN)
		return CORNER;


	


	if (x > 40)
	{
		if (BoardPosition[x + 4][y] == 1 || BoardPosition[x + 4][y + 1] == 1 || BoardPosition[x + 4][y + 2] == 1)
			return true;
	}
	else if (BoardPosition[x-1][y] == 1 || BoardPosition[x -1][y + 1] == 1 || BoardPosition[x -1][y + 2] == 1)
		return true;
	return false;*/

}

