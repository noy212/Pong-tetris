#include "Game.h"


char Game::showManu()
{
	char c;

	setState(state::MANU);
	printGameState();
	setColor(COLOR::TEAL_FADE_TEXT);
	cout << "		1)Start new game Human vs Human" << endl;
	cout << "		2)Start new game Human vs Computer" << endl;
	cout << "		3)Start new game Computer vs Computer" << endl;
	if (pausedGame)
		cout << "		4)Continue a paused game" << endl;
	if (getState() != INSTRUCTIONS)
		cout << "		8)Present instructions and keys" << endl;
	cout << "		9)EXIT" << endl;
	cin >> c;
	system("cls");
	return c;
}



void Game::goToState(KeyboardManager &kbManager, Screen &tetrisManager, Board** users) {
	char c;
	switch (getState())
	{
	case NEW_GAME_HH:
	{
		setFirstBombL(true);
		setFirstBombR(true);
		ball->setBehavior(&regularball, Ball::stateNameTypes::Regular);
		pausedGame = false;
		setState(NEW_GAME_HH);
		setLPlayer(users[0]);
		setRPlayer(users[1]);
		changeGameStatus(false);
		StartGame(kbManager, tetrisManager);
		system("cls");
		tetrisManager.freeAllBoard();
		break;
	}
	case NEW_GAME_HC:
	{
		setFirstBombL(true);
		setFirstBombR(true);
		ball->setBehavior(&regularball, Ball::stateNameTypes::Regular);
		pausedGame = false;
		setState(NEW_GAME_HC);
		setLPlayer(users[0]);
		setRPlayer(users[3]);

		printGameState();
		setColor(COLOR::TEAL_FADE_TEXT);
		cout << "				a)Best" << endl;
		cout << "				b)Good" << endl;
		cout << "				c)Novice" << endl;
		cin >> c;
		system("cls");
		dynamic_cast<PcBoard*>(right_player)->setLevel(c);
		changeGameStatus(false);
		StartGame(kbManager, tetrisManager);
		system("cls");
		tetrisManager.freeAllBoard();
		break; }
	case NEW_GAME_CC:
	{
		setFirstBombL(true);
		setFirstBombR(true);
		ball->setBehavior(&regularball, Ball::stateNameTypes::Regular);
		pausedGame = false;
		setState(NEW_GAME_HC);

		setLPlayer(users[2]);
		setRPlayer(users[3]);
		

		printGameState();
		setColor(COLOR::TEAL_FADE_TEXT);
		cout << "				left player:" << endl;
		cout << "				a)Best" << endl;
		cout << "				b)Good" << endl;
		cout << "				c)Novice" << endl;
		cin >> c;
		system("cls");
		dynamic_cast<PcBoard*>(left_player)->setLevel(c);
		printGameState();
		setColor(COLOR::TEAL_FADE_TEXT);
		cout << "				right player:" << endl;
		cout << "				a)Best" << endl;
		cout << "				b)Good" << endl;
		cout << "				c)Novice" << endl;
		cin >> c;
		system("cls");
		dynamic_cast<PcBoard*>(right_player)->setLevel(c);
		


		changeGameStatus(false);
		StartGame(kbManager, tetrisManager);
		system("cls");
		tetrisManager.freeAllBoard();
		break;
	}
	case RESUME_GAME:
	{
		setState(RESUME_GAME);
		break;
	}
	case INSTRUCTIONS:
	{

		pausedGame = false;
		setState(INSTRUCTIONS);
		setColor(COLOR::GRAY_TEXT);

		printGameState();
		setColor(COLOR::TEAL_FADE_TEXT);
		cout << "	This is a pong game for two players." << endl;
		cout << "	You can move the Players using the keyboard, left Player: UP-'q' DOWN-'a', right Player: UP-'p' DOWN-'l'" << endl;
		cout << "	once you misses the ball Tetris game will start" << endl;
		cout << "	The game allows to play against the computer." << endl;
		cout << "	The computer have 3 levels: (a)BEST(b) GOOD and (C)NOVICE" << endl;
		cout << "	you can turn the Ball into a Bomb." << endl;
		cout << "	Left player Bomb key is 's' or 'S' key" << endl;
		cout << "	Right player Bomb key is 'k' or 'K' key" << endl;
		cout << "	Once pressed, the Ball turns into becoming a Bomb for 8 game iterations, then the Ball becomes a Bomb." << endl;
		cout << "	Enjoy!" << endl << endl;

		cout << "	To return menu ";
		system("pause");
		system("cls");
		char state = showManu();
		setState(state - '0');
		goToState(kbManager, tetrisManager,users);
		break;
	}
	case EXIT:
	{
		pausedGame = false;
		setState(EXIT);
	}

	}

}

void Game::StartGame(KeyboardManager &kbManager, Screen &tetrisManager)
{
	getLPlayer().reset_player(l_x, l_up_y, l_down_y);
	getRPlayer().reset_player(r_x, r_up_y, r_down_y);
	resetCounters();
	tetrisManager.freeAllBoard();
	tetrisManager.drawScreen();
	ball->resetBall();
	ball->draw();
	
	while (!gameStatus() && (getState() != EXIT))
	{
		left_player->draw(COLOR::GREEN_BACKGROUND);
		right_player->draw(COLOR::GREEN_BACKGROUND);
		startPongGame(kbManager, tetrisManager);

		getBall().start_new_ball();

		if (check_missed_left() && !gameStatus())
		{	// one of the player MISSED the ball - start tetris
			setLCounter();
			if (left_player->get_up().get_X() < Game::lose::l)
			{
				UserBoard dead_left_player({ left_player->get_up().get_X(),left_player->get_up().get_Y(),'#' },
				{ left_player->get_up().get_X(),left_player->get_down().get_Y(),'#' }, Board::Left, LKEYS);
				tetrisManager.updateBoardPosition(*left_player, dead_left_player);
				left_player->moveRL(Board::Right);

			}
			else
				changeGameStatus(true); // the left player lose the game
		}
		else if (!gameStatus())
		{
			setRCounter();

			if (right_player->get_up().get_X() > Game::lose::r) {
				UserBoard dead_left_player({ right_player->get_up().get_X(),right_player->get_up().get_Y(),'#' },
				{ right_player->get_up().get_X(),right_player->get_down().get_Y(),'#' }, Board::Right, RKEYS);
				tetrisManager.updateBoardPosition(*right_player, dead_left_player);
				right_player->moveRL(Board::Left);

			}
			else
				changeGameStatus(true); // the right player lose the game
		}

		setColor(COLOR::GRAY_TEXT);
		gotoxy(37, 2);
		cout << right_counter << " - " << left_counter;

		reset_missed();

	}
	
}








void Game::startPongGame(KeyboardManager & kbManager, Screen & tetrisManager)
{

	Board::HitBoard leftStatus;
	Board::HitBoard rightStatus;
	left_player->WinOrLose();
	right_player->WinOrLose();

	while (!(check_missed_left() || check_missed_right()))
	{
		if(ball->get_x() == 40)
			updateCountBomb();
		ball->getBehavior()->setIteration();
		if (!kbManager.handleKeyboard())
		{	//ESC was pressed
			system("cls");
			pausedGame = true;
			char state = showManu();
			setState(state - '0');
			if (getState() != RESUME_GAME)
			{	// dont continue the game
				changeGameStatus(true);
				return;
			}
			tetrisManager.drawScreen();
			tetrisManager.drawDeadBoard();
			left_player->draw(COLOR::GREEN_BACKGROUND);
			right_player->draw(COLOR::GREEN_BACKGROUND);
		}
		if (ball->getBehavior()->changeState()) // change the ball state inside the game based on the curr state
			changeBallState();
		left_player->moveBoard();
		right_player->moveBoard();
		Sleep(50);
		ball->move();
		leftStatus = left_player->checkHit(*ball);
		rightStatus = right_player->checkHit(*ball);
		if (leftStatus == Board::MISSED || rightStatus == Board::MISSED)
			missedHit(leftStatus, rightStatus, tetrisManager);
		else if (leftStatus == Board::CENTER || rightStatus == Board::CENTER)
			centerHit(leftStatus, rightStatus);
		else if (leftStatus == Board::CORNER || rightStatus == Board::CORNER)
			cornerHit(leftStatus, rightStatus);
		if(dynamic_cast<PcBoard*>(left_player))
			randomlyPcBomb(Board::Left);
		if (dynamic_cast<PcBoard*>(right_player))
			randomlyPcBomb(Board::Right);
	}
}

void Game::centerHit(Board::HitBoard leftStatus, Board::HitBoard rightStatus) {
	if (ball->getStateName() == Ball::stateNameTypes::Bomb)
	{
		if (leftStatus == Board::CENTER)
		{
			left_player->setXBoard(3);
			setLCounter(2);
		}
		else
		{
			right_player->setXBoard(-3);
			setRCounter(2);
		}
		change_missed_status();

	}
	else if (ball->getStateName() == Ball::stateNameTypes::Becoming)
		ball->setBehavior(&regularball, Ball::stateNameTypes::Regular);
	ball->changeXdir();
	ball->animate(Ball::CENTER, ball->getXDir()*(-1));

	left_player->WinOrLose();
	right_player->WinOrLose();
}


void Game::cornerHit(Board::HitBoard leftStatus, Board::HitBoard rightStatus) {
	if (ball->getStateName() == Ball::stateNameTypes::Bomb)
	{
		if (leftStatus == Board::CORNER)
		{
			left_player->setXBoard(3);
			setLCounter(2);
		}
		else
		{
			right_player->setXBoard(-3);
			setRCounter(2);
		}
		change_missed_status();
	}
	else if (ball->getStateName() == Ball::stateNameTypes::Becoming)
		ball->setBehavior(&regularball, Ball::stateNameTypes::Regular);
	ball->changeYdir();
	ball->changeXdir();
	ball->animate(Ball::CORNER, ball->getXDir()*(-1));

	left_player->WinOrLose();
	right_player->WinOrLose();
}


void Game::missedHit(Board::HitBoard leftStatus, Board::HitBoard rightStatus, Screen & tetrisManager) {
	if (ball->getStateName() == Ball::stateNameTypes::Regular)
		change_missed_status();
	else if (tetrisManager.missedBoard(ball, left_player, right_player))
		change_missed_status();
}

void Game::randomlyPcBomb(Board::BoardSide playerSide) {
	// this function check if the computer can send bomb - if yes randomly change the status
	int poll;
	if (ball->getStateName() == Ball::stateNameTypes::Regular &&  ball->get_x() + 4 <= right_player->get_up().get_X() && ball->get_x() >= left_player->get_up().get_X()) { // the ball between the two players and regular
		if (playerSide == Board::Left && ball->getXDir() == 1) {
			// randomly 10%
			poll = rand() % 500;
			if (poll < 10) {
				ball->setBehavior(&becomingbomb, Ball::stateNameTypes::Becoming);
				ball->getBehavior()->resetIteration();
				avoidBomb();
			}
				
		}
		if (playerSide == Board::Right && ball->getXDir() == -1) {
			// randomly 10%
			poll = rand() % 500;
			if (poll < 10) {
				ball->setBehavior(&becomingbomb, Ball::stateNameTypes::Becoming);
				ball->getBehavior()->resetIteration();
				avoidBomb();
			}
		}
	}
}


void Game::printGameState() {
	setColor(COLOR::GRAY_TEXT);
	switch (getState())
	{
	case MANU:
	{

		cout << R"(

		::::    ::::  :::::::::: ::::    ::: :::    :::
		+:+:+: :+:+:+ :+:        :+:+:   :+: :+:    :+:
		+:+ +:+:+ +:+ +:+        :+:+:+  +:+ +:+    +:+
		+#+  +:+  +#+ +#++:++#   +#+ +:+ +#+ +#+    +:+
		+#+       +#+ +#+        +#+  +#+#+# +#+    +#+
		#+#       #+# #+#        #+#   #+#+# #+#    #+#
		###       ### ########## ###    ####  ######## 


)";
		break;
	}

	case NEW_GAME_HC:
	case NEW_GAME_CC:
	{
		cout << R"(
		  ____  _  __  __ _            _ _         
		 |  _ \(_)/ _|/ _(_) ___ _   _| | |_ _   _ 
		 | | | | | |_| |_| |/ __| | | | | __| | | |
		 | |_| | |  _|  _| | (__| |_| | | |_| |_| |
		 |____/|_|_| |_| |_|\___|\__,_|_|\__|\__, |
		                                     |___/ 


)";
		break;
	}
	case INSTRUCTIONS:
	{

		cout << R"(

		  _____           _                   _   _                 
		 |_   _|         | |                 | | (_)                
		   | |  _ __  ___| |_ _ __ _   _  ___| |_ _  ___  _ __  ___ 
		   | | | '_ \/ __| __| '__| | | |/ __| __| |/ _ \| '_ \/ __|
		  _| |_| | | \__ \ |_| |  | |_| | (__| |_| | (_) | | | \__ \
		 |_____|_| |_|___/\__|_|   \__,_|\___|\__|_|\___/|_| |_|___/
                                                            
                                                            

)";
		break;
	}
	case GAME_OVER: {
		cout << R"(

	  ____   ____  ___ ___    ___       ___   __ __    ___  ____  
	 /    | /    ||   |   |  /  _]     /   \ |  |  |  /  _]|    \ 
	|   __||  o  || _   _ | /  [_     |     ||  |  | /  [_ |  D  )
	|  |  ||     ||  \_/  ||    _]    |  O  ||  |  ||    _]|    / 
	|  |_ ||  _  ||   |   ||   [_     |     ||  :  ||   [_ |    \ 
	|     ||  |  ||   |   ||     |    |     | \   / |     ||  .  \
	|___,_||__|__||___|___||_____|     \___/   \_/  |_____||__|\_|
                                                              

)";
		break;
	}
	}
}


void Game::changeBallState() {
	switch (ball->getStateName())
	{
	case Ball::stateNameTypes::Regular: {
		// start all the bomb iterations only if this is the fisrt time OR there is more that 4 times x=40
		if (checkBombOption()) {
			ball->setBehavior(&becomingbomb, Ball::stateNameTypes::Becoming);
			avoidBomb();
		}
		break;
	}

	case Ball::stateNameTypes::Becoming: {
		ball->getBehavior()->resetIteration();// reset the iteration of the Becoming
		ball->setBehavior(&bombBall, Ball::stateNameTypes::Bomb);
		break;

	}
	case Ball::stateNameTypes::Bomb: {
		// first check if the ball inside the boards, is yes-> change state; else-> continue as a bomb
		if (ball->get_x()+4 < right_player->get_up().get_X() && ball->get_x()-1 > left_player->get_up().get_X()) {
			ball->getBehavior()->resetIteration();	// reset the iteration of the Bomb
			ball->setBehavior(&regularball, Ball::stateNameTypes::Regular);
		}
		break;	// continue as a bomb
	}
	}
}

void Game::avoidBomb() {
	// if the pc will need to miss the ball
	if (ball->get_x() + 3 + 7 < right_player->get_up().get_X() && ((right_player->get_up().get_X()) - (ball->get_x() + 3 + 8)) <= 4)
	{
		if (dynamic_cast<PcBoard*>(right_player) != nullptr && dynamic_cast<PcBoard*>(right_player)->getLevel() == PcBoard::Best)
			right_player->lose(100);
		else
			right_player->lose(rand() % 100);
	}
	else if (ball->get_x() - 7 > left_player->get_up().get_X() && (ball->get_x() - 8) - left_player->get_up().get_X() <= 4)
	{
		if (dynamic_cast<PcBoard*>(left_player) != nullptr && dynamic_cast<PcBoard*>(left_player)->getLevel() == PcBoard::Best)
			left_player->lose(100);
		else
			left_player->lose(rand() % 100);
	}
}


void Game::updateCountBomb() {
	// this function update the map of counters. call whene x=40
	if(ball->getBehavior()->getLBombStatus())
		countBomb[BallBehavior::ballside::left] += 1;
	if (ball->getBehavior()->getRBombStatus())
		countBomb[BallBehavior::ballside::right] += 1;
}

bool Game::checkBombOption() {
	// this function check if player can start a bomb
	if (ball->getBehavior()->getLBombStatus()) {
		if (countBomb[BallBehavior::ballside::left] >= 4 || getFirstBombL()) {
			setFirstBombL(false);
			countBomb[BallBehavior::ballside::left] = 0;
			ball->getBehavior()->setLBombStatus(false);
			return true;
		}
	}
	if (ball->getBehavior()->getRBombStatus()) {
		if (countBomb[BallBehavior::ballside::right] >= 4 || getFirstBombR()) {
			setFirstBombR(false);
			countBomb[BallBehavior::ballside::right] = 0;
			ball->getBehavior()->setRBombStatus(false);
			return true;
		}
	}
	return false;
}

