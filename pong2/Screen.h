#pragma once

#include "Board.h"
#include "UserBoard.h"
#include "PcBoard.h"

class Screen 
{
public:
	enum { MAX_X = 80, MAX_Y = 25 };
	int BoardPosition[Board::max_x+1][Board::max_y+1] = {};


	static bool checkXLimit(const Point &p)
	{
		return (p.get_X() == Board::min_x || p.get_X() == Board::max_x);
	}
	static bool checkYLimit(const Point &p)
	{
		return (p.get_Y() == Board::min_y || p.get_Y() == Board::max_y);
	}
	
	bool missedBoard(Ball *b, Board *left_player, Board *right_player);
	int hitDead(Ball *ball, Board::BoardSide side);

	bool checkFreePosition(const int &x_up, const int &y_up,const Board::BoardSide &side) const;
	void updateBoardPosition(Board& originalPlayer, Board &player);
	void freeBoardPosition(const int &x, const int &y);
	bool emptyLine(int x);
	bool checkFullLine(int x, const Board &player);
	void bombHitDead(Board::BoardSide side, int playerPos, Board& left_player, Board& right_player, Ball& ball, const int& LineToerase);
	void bombHitEdge(Board::BoardSide side, int playerPos, Board& left_player, Board& right_player, Ball& ball);
	void moveDeadBoards(const int &max_x, const int &ereasedLine, const Board::BoardSide &side);
	void updateBoardValues(const int &x, const int &y);
	void eraseLine(const int &x);
	void drawDeadBoard();
	void drawScreen();

	void freeAllBoard();
};
