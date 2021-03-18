#pragma once

#include "Screen.h"
#include "KeyboardManager.h"
#include "BombBall.h"
#include "RegularBall.h"
#include "BecomingBomb.h"
#define LKEYS "qa"
#define RKEYS "pl"


class Game
{
	Board* left_player;
	Board* right_player;
	Ball* ball;
	BombBall bombBall;
	RegularBall regularball;
	BecomingBomb becomingbomb;
	KeyboardManager* kbManager;
	std::map<BallBehavior::ballside, int> countBomb{};
	bool firstRunningBombL = true;
	bool firstRunningBombR = true;
	unsigned int state;
	bool gameOver = false;
	unsigned int left_counter = 0;
	unsigned int right_counter = 0;
	bool left_player_missed = false;
	bool right_player_missed = false;
	bool pausedGame = false;

public:
	enum lose {l = 20, r = 60};
	enum state{NEW_GAME_HH=1, NEW_GAME_HC = 2, NEW_GAME_CC = 3, RESUME_GAME=4, INSTRUCTIONS=8,EXIT=9 , MANU=0, GAME_OVER=10};
	enum { l_x = 4, l_up_y = 13, l_down_y = 15, r_x = 76, r_up_y = 13, r_down_y = 15 };

	Game(Board* lplayer1, Board* rplayer1,Ball* ball1, const unsigned int state, KeyboardManager* kbManager) : left_player(lplayer1), right_player(rplayer1), ball(ball1), state(state), kbManager(kbManager)
	{
		kbManager->addtoKbList(&regularball);
	}
	bool getPausedStatus() {
		return pausedGame;
	}
	void changeBallState();
	char showManu();
	void goToState(KeyboardManager &kbManager, Screen &tetrisManager, Board** users);
	void StartGame(KeyboardManager &kbManager, Screen &tetrisManager);
	void startPongGame(KeyboardManager &kbManager, Screen &tetrisManager);
	void printGameState();
	bool getFirstBombL() {
		return firstRunningBombL;
	}
	void setFirstBombL(bool state) {
		firstRunningBombL = state;
	}
	bool getFirstBombR() {
		return firstRunningBombR;
	}
	void setFirstBombR(bool state) {
		firstRunningBombR = state;
	}
	void setState(const int &i)
	{
		state = i;
	}
	const int& getState() 
	{
		return state;
	}
	Ball& getBall() 
	{
		return *ball;
	}

	void setLPlayer(Board* newP)
	{
		left_player = newP;
	}
	void setRPlayer(Board* newP)
	{
		right_player = newP;
	}

	Board& getLPlayer() 
	{
		return *left_player;
	}
	Board& getRPlayer()
	{
		return *right_player;
	}
	const bool gameStatus() 
	{
		return gameOver;
	}
	void changeGameStatus(const bool &val) 
	{
		gameOver = val;
	}
	void change_missed_status() 
	{
		if(ball->get_x()>40)
			right_player_missed = true;
		else
			left_player_missed = true;
	}
	bool check_missed_left() {
		return left_player_missed;
	}
	bool check_missed_right() {
		return right_player_missed;
	}
	void reset_missed() {
		left_player_missed = false;
		right_player_missed = false;
	}
	const int & getLCounter() const {
		return left_counter;
	}
	const int & getRCounter() const {
		return right_counter;
	}
	void setLCounter(const int &n=1) {
		left_counter+=n;
	}
	void setRCounter(const int &n = 1) {
		right_counter+=n;
	}
	void updateCountBomb();
	bool checkBombOption();
	void randomlyPcBomb(Board::BoardSide playerSide);
	void resetCounters()
	{
		left_counter = 0;
		right_counter = 0;
	}
	void avoidBomb();
	void centerHit(Board::HitBoard leftStatus, Board::HitBoard rightStatus);
	void cornerHit(Board::HitBoard leftStatus, Board::HitBoard rightStatus);
	void missedHit(Board::HitBoard leftStatus, Board::HitBoard rightStatus, Screen & tetrisManager);


};