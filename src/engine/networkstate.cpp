#include "networkstate.h"
#include "inputhandler.h"
#include "text.h"
#include "image.h"
#include "game.h"
#include "networkmanager.h"

const std::string NetworkState::networkId = "IDNetwork";

NetworkState::NetworkState() {}

bool
NetworkState::onEnter()
{
	Render * render = Render::getInstance();
	render->setColor(255, 255, 255, 255);
	render->clear();

	SDL_Color black = {0, 0, 0, 255};

	this->texts["title"] = new Text("Multiplayer", 50);
	this->texts["title"]->setFont("resources/font/Army.ttf");
	this->texts["title"]->setColor(black);

	int x = (Game::Instance()->getWindow()->getWidth() / 2) - (this->texts["title"]->getWidth() / 2);
	int y = 50;
	this->texts["title"]->setPosition(x, y);

	y += this->texts["title"]->getHeight() + 100;

	this->buttons["createRoom"] = new MenuButton(x, y, "resources/img/createroom_button.png", "createRoom", 3, true);
	x = (Game::Instance()->getWindow()->getWidth() / 4) - (this->buttons["createRoom"]->getWidth() / 2);
	this->buttons["createRoom"]->setPosition(x, y);
	this->buttons["createRoom"]->setEventListener(this);
	this->buttons["createRoom"]->setAudioOnClick("resources/audio/fx_stab-001.wav", "playClick");
	InputHandler::getInstance()->addMouseClick(this->buttons["createRoom"]);

	this->buttons["joinRoom"] = new MenuButton(x, y, "resources/img/joinroom_button.png", "joinRoom", 3, true);
	x = (Game::Instance()->getWindow()->getWidth()*0.75) - (this->buttons["joinRoom"]->getWidth() / 2);
	this->buttons["joinRoom"]->setPosition(x, y);
	this->buttons["joinRoom"]->setEventListener(this);
	this->buttons["joinRoom"]->setAudioOnClick("resources/audio/fx_stab-001.wav", "playClick");
	InputHandler::getInstance()->addMouseClick(this->buttons["joinRoom"]);

	this->textfields["ip"] = new TextField(x, y, 300, 30);
	x = (Game::Instance()->getWindow()->getWidth() / 2) - (this->textfields["ip"]->getWidth() / 2);
	y += this->buttons["createRoom"]->getHeight() + this->textfields["ip"]->getHeight()*3;
	this->textfields["ip"]->setPosition(x, y);
	this->textfields["ip"]->init();
	InputHandler::getInstance()->addMouseClick(this->textfields["ip"]);
	
	this->texts["ip"] = new Text("IP:", 30);
	this->texts["ip"]->setFont("resources/font/Army.ttf");
	this->texts["ip"]->setColor(black);
	x -= this->texts["ip"]->getWidth();
	y += 5;
	this->texts["ip"]->setPosition(x, y);

	this->textfields["name"] = new TextField(x, y, 300, 30);
	x = (Game::Instance()->getWindow()->getWidth() / 2) - (this->textfields["name"]->getWidth() / 2);
	y += this->textfields["ip"]->getHeight()*2;
	this->textfields["name"]->setPosition(x, y);
	this->textfields["name"]->init();
	InputHandler::getInstance()->addMouseClick(this->textfields["name"]);

	this->texts["name"] = new Text("Name:", 30);
	this->texts["name"]->setFont("resources/font/Army.ttf");
	this->texts["name"]->setColor(black);
	x -= this->texts["name"]->getWidth();
	y += 5;
	this->texts["name"]->setPosition(x, y);

	this->ipError = new Warn("You typed the wrong IP", "resources/img/warnok.png",
							"resources/audio/fx_stab-001.wav", "resources/font/Army.ttf");
	this->ipError->init();

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
	for(map<std::string, MenuButton *>::iterator it = this->buttons.begin(); it != this->buttons.end(); it++)
		it->second->update();
	for(map<std::string, TextField *>::iterator it = this->textfields.begin(); it != this->textfields.end(); it++)
		it->second->update();
}

void 
NetworkState::render()
{
	for(map<std::string, Text *>::iterator it = this->texts.begin(); it != this->texts.end(); it++)
		it->second->draw();
	for(map<std::string, MenuButton *>::iterator it = this->buttons.begin(); it != this->buttons.end(); it++)
		it->second->draw();
	for(map<std::string, TextField *>::iterator it = this->textfields.begin(); it != this->textfields.end(); it++)
		it->second->draw();
	ipError->draw();
}

bool
NetworkState::onExit()
{
	for(map<std::string, Text *>::iterator it = this->texts.begin(); it != this->texts.end(); it++)
		delete it->second;
	for(map<std::string, MenuButton *>::iterator it = this->buttons.begin(); it != this->buttons.end(); it++)
	{
		InputHandler::getInstance()->removeMouseClick(it->second);
		delete it->second;
	}
	for(map<std::string, TextField *>::iterator it = this->textfields.begin(); it != this->textfields.end(); it++)
	{
		InputHandler::getInstance()->removeMouseClick(it->second);
		delete it->second;
	}
	return true;
}

void 
NetworkState::onMouseClick(MouseClick *mouseClick)
{
    if(mouseClick == this->buttons["createRoom"])
	{
        //create
	}
    else if(mouseClick == this->buttons["joinRoom"])
	{
        //join
	}
	/*std::string nome = NetworkManager::Instance()->nome;
	int tipo  = NetworkManager::Instance()->tipo;
	std::string ip = NetworkManager::Instance()->ip;

	if(tipo == 1)
		NetworkManager::Instance()->joinRoom(nome, ip);
	else
		NetworkManager::Instance()->createRoom(nome, ip);

	NetworkManager::Instance()->launchCommunication();*/
}

