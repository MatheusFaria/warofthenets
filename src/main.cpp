#include "game.h"
#include "networkmanager.h"
#include <iostream>

int main()
{

	int tipo = 1;
	std::string ip, nome;

	ip = "10.1.1.154";
	nome = "lucas";

    
	NetworkManager::Instance()->tipo = tipo;
	NetworkManager::Instance()->ip = ip;
	NetworkManager::Instance()->nome = nome;
	

	if(tipo == 0)
		NetworkManager::Instance()->joinRoom(nome, ip);
	else
		NetworkManager::Instance()->createRoom(nome, ip);

	
	NetworkManager::Instance()->launchCommunication();

	Game::Instance()->init();
	Game::Instance()->run();
	Game::Instance()->clean();

	return 0;
}

