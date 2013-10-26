#include "game.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	if(argc == 1 || argc > 2)
	{
		printf("Deve-se passar 2 argumentos [IP e porta do servidor");
		exit(1);
	}

	Game::Instance()->init();
	Game::Instance()->run();
	Game::Instance()->clean();

	return 0;
}

