#include "game.h"
#include "networkmanager.h"
#include <iostream>

int main()
{

	Game::Instance()->init();
	Game::Instance()->run();
	Game::Instance()->clean();

	return 0;
}

