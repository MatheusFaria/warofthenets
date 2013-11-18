#include "game.h"
#include "networkmanager.h"
#include <iostream>

int main()
{
	
	//int tipo;
	//std::string ip, nome;
	
/*	std::cout << " Digite o IP do servidor: ";
	std::cin >> ip;
	
	std::cout << "\n Digite 1 para ser o servidor," << std::endl;
	std::cout << "ou 0 para ser o cliente: ";
    std::cin >> tipo;
* tipo = 0;

	ip = "127.0.0.1";
	nome = "servidor";
    
	NetworkManager::Instance()->tipo = tipo;
	NetworkManager::Instance()->ip = ip;
	NetworkManager::Instance()->nome = nome;
	

	if(tipo == 0)
		NetworkManager::Instance()->joinRoom(nome, ip);
	else
		NetworkManager::Instance()->createRoom(nome, ip);

	
	NetworkManager::Instance()->launchCommunication();
	*/

	Game::Instance()->init();
	Game::Instance()->run();
	Game::Instance()->clean();

	return 0;
}

