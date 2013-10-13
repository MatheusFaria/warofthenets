#include "game.h"

int main()
{

	Game::Instance()->init();
	Game::Instance()->run();
	Game::Instance()->clean();

	return 0;
}

