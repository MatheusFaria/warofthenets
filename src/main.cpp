#include "game.h"
#include "networkmanager.h"
#include <iostream>

int main()
{

	int tipo = 1;
	std::string ip, nome;

	ip = "10.1.1.144";
	nome = "lucas";

	if(tipo == 1)
		NetworkManager::Instance()->joinRoom(nome, ip);
	else
		NetworkManager::Instance()->createRoom(nome, ip);

	NetworkManager::Instance()->tipo = tipo;
	NetworkManager::Instance()->ip = ip;
	NetworkManager::Instance()->nome = nome;

	Game::Instance()->init();
	Game::Instance()->run();
	Game::Instance()->clean();

	return 0;
}

