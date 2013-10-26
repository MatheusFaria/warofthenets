#include "game.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	if(argc == 2 || argc > 3)
	{
		printf("Deve-se passar 2 argumentos [IP e porta do servidor");
		exit(1);
	}

	Game::Instance()->init(argc, argv);
	Game::Instance()->run();
	Game::Instance()->clean();

	return 0;
}

