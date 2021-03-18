#include <map>
#include <iterator>
#include "Game.h"
#define LKEYS "qa"
#define RKEYS "pl"


int main() {

	hideConsoleCursor();
	Ball ball;
	UserBoard ulplayer({ Game::l_x, Game::l_up_y,'#' }, { Game::l_x, Game::l_down_y,'#' }, Board::Left, LKEYS);
	UserBoard urplayer({ Game::r_x, Game::r_up_y,'#' }, { Game::r_x, Game::r_down_y,'#' }, Board::Right, RKEYS);
	PcBoard plplayer({ Game::l_x, Game::l_up_y,'#' }, { Game::l_x, Game::l_down_y,'#' }, Board::Left,PcBoard::Best,&ball);
	PcBoard prplayer({ Game::l_x, Game::l_up_y,'#' }, { Game::l_x, Game::l_down_y,'#' }, Board::Right, PcBoard::Best, &ball);

	Board* users[4] = { &ulplayer, &urplayer, &plplayer, &prplayer };

	Screen tetrisManager;
	KeyboardManager kbManager{};
	Game pong(&ulplayer,&urplayer, &ball, 0, &kbManager);
	kbManager.addtoKbList(&ulplayer);
	kbManager.addtoKbList(&urplayer);

	char state = pong.showManu();
	pong.setState(state - '0');
	while (pong.getState() != 9) {
		pong.goToState(kbManager, tetrisManager, users);
		if ( pong.getPausedStatus() == false&& pong.getState() != 9)
		{
			int l= pong.getLCounter();
			int r = pong.getRCounter();
			setColor(COLOR::GRAY_TEXT);
			pong.setState(Game::state::GAME_OVER);
			pong.printGameState();
			setColor(COLOR::TEAL_FADE_TEXT);
			if (l > r)
				cout << "			Right player win" << endl << endl;
			else if (l < r)
				cout << "			Left player win" << endl << endl;

			system("pause");
			system("cls");
		 state = pong.showManu();
		 pong.setState(state - '0');

		}
	}
}
