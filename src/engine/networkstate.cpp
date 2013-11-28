#include "networkstate.h"
#include "playstate.h"
#include "fasestate.h"
#include "inputhandler.h"
#include "soundmanager.h"
#include "text.h"
#include "image.h"
#include "game.h"
#include "networkmanager.h"


const std::string NetworkState::networkId = "IDNetwork";

NetworkState::NetworkState() {}

bool
NetworkState::onEnter()
{
	SoundManager::Instance()->loadSound("resources/audio/Stage5_Hitman.ogg","network", MUSIC);
	SoundManager::Instance()->playMusic("network", -1);

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
	this->textfields["ip"]->setEventListener(this);
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
	this->textfields["name"]->setEventListener(this);
	InputHandler::getInstance()->addMouseClick(this->textfields["name"]);

	this->texts["name"] = new Text("Name:", 30);
	this->texts["name"]->setFont("resources/font/Army.ttf");
	this->texts["name"]->setColor(black);
	x -= this->texts["name"]->getWidth();
	y += 5;
	this->texts["name"]->setPosition(x, y);

	this->warn = new Warn("You typed the wrong IP", "resources/img/warnok.png",
							"resources/audio/fx_stab-001.wav", "resources/font/Army.ttf");
	this->warn->init();
	this->warn->setShow(false);
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
	if(this->warn->getShow())
		this->disableAllClicks();
	else
		this->enableAllClicks();
	for(map<std::string, MenuButton *>::iterator it = this->buttons.begin(); it != this->buttons.end(); it++)
		it->second->update();
	for(map<std::string, TextField *>::iterator it = this->textfields.begin(); it != this->textfields.end(); it++)
		it->second->update();
	this->warn->update();
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
	this->warn->draw();
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

	SoundManager::Instance()->stopSound();
	SoundManager::Instance()->clearFromSoundManager("network", MUSIC);

	return true;
}

void 
NetworkState::onMouseClick(MouseClick *mouseClick)
{
    if(mouseClick == this->buttons["createRoom"])
	{
        if(textfields["ip"]->getText() == "")
		{
			this->warn->setText("You typed the IP wrong.");
			this->warn->setShow(true);
			return;
		}
        else if(textfields["name"]->getText() == "")
		{
			this->warn->setText("You typed the name wrong.");
			this->warn->setShow(true);
			return;
		}

		NetworkManager::Instance()->setTipo(1);
		NetworkManager::Instance()->setIp(textfields["ip"]->getText());
		NetworkManager::Instance()->setNome(textfields["name"]->getText());
		NetworkManager::Instance()->createRoom(textfields["name"]->getText(),textfields["ip"]->getText());
		NetworkManager::Instance()->launchCommunication();
		//Game::Instance()->getStateMachine()->pushState(new PlayState());
		Game::Instance()->getStateMachine()->changeState(new FaseState());
		
	}
    else if(mouseClick == this->buttons["joinRoom"])
	{
        if(textfields["ip"]->getText() == "")
		{
			this->warn->setText("You typed the IP wrong.");
			this->warn->setShow(true);
			return;
		}
        else if(textfields["name"]->getText() == "")
		{
			this->warn->setText("You typed the name wrong.");
			this->warn->setShow(true);
			return;
		}
		NetworkManager::Instance()->setTipo(0);
		NetworkManager::Instance()->setIp(textfields["ip"]->getText());
		NetworkManager::Instance()->setNome(textfields["name"]->getText());
		NetworkManager::Instance()->joinRoom(textfields["name"]->getText(),textfields["ip"]->getText());
		NetworkManager::Instance()->launchCommunication();
		//Game::Instance()->getStateMachine()->pushState(new PlayState());
		Game::Instance()->getStateMachine()->changeState(new FaseState());
	}
	
	else if(mouseClick == this->textfields["ip"])
	{
	    this->textfields["name"]->setFocused(false);
	    this->textfields["ip"]->setFocused(true);
	}
	else if(mouseClick == this->textfields["name"])
	{
	    this->textfields["ip"]->setFocused(false);
	    this->textfields["name"]->setFocused(true);
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

void
NetworkState::enableAllClicks()
{
	for(map<std::string, MenuButton *>::iterator it = this->buttons.begin(); it != this->buttons.end(); it++)
		it->second->setActive(true);
	for(map<std::string, TextField *>::iterator it = this->textfields.begin(); it != this->textfields.end(); it++)
		it->second->setActive(true);
}

void
NetworkState::disableAllClicks()
{
	for(map<std::string, MenuButton *>::iterator it = this->buttons.begin(); it != this->buttons.end(); it++)
		it->second->setActive(false);
	for(map<std::string, TextField *>::iterator it = this->textfields.begin(); it != this->textfields.end(); it++)
		it->second->setActive(false);
}