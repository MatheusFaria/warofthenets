#include "networkstate.h"
#include "networkmanager.h"

bool
NetworkState::onEnter()
{

	std::string nome = NetworkManager::Instance()->nome;
	int tipo  = NetworkManager::Instance()->tipo;
	std::string ip = NetworkManager::Instance()->ip;

	if(tipo == 1)
		NetworkManager::Instance()->joinRoom(nome, ip);
	else
		NetworkManager::Instance()->createRoom(nome, ip);

	NetworkManager::Instance()->launchCommunication();
	return true;

}

bool
NetworkState::onExit()
{
	return true;
}
