#include "networkstate.h"
#include "inputhandler.h"
#include "networkmanager.h"

const std::string NetworkState::networkId = "IDNetwork";

NetworkState::NetworkState() {}

bool
NetworkState::onEnter()
{
	this->txtField = new TextField(100, 100, "resources/img/textFieldShape.png", 30, 70);
	this->txtField->init();

	InputHandler::getInstance()->addMouseClick(this->txtField);
	/*std::string nome = NetworkManager::Instance()->nome;
	int tipo  = NetworkManager::Instance()->tipo;
	std::string ip = NetworkManager::Instance()->ip;

	if(tipo == 1)
		NetworkManager::Instance()->joinRoom(nome, ip);
	else
		NetworkManager::Instance()->createRoom(nome, ip);

	NetworkManager::Instance()->launchCommunication();*/
	return true;

}

std::string
NetworkState::getStateId() const
{
	return NetworkState::networkId;
}

void 
NetworkState::update()
{
	this->txtField->update();
}

void 
NetworkState::render()
{
	this->txtField->draw();
}

bool
NetworkState::onExit()
{
	delete this->txtField;
	InputHandler::getInstance()->removeMouseClick(this->txtField);
	return true;
}
