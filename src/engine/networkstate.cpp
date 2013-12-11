#include "networkstate.h"
#include "playstate.h"
#include "fasestate.h"
#include "menustate.h"
#include "inputhandler.h"
#include "soundmanager.h"
#include "SDL2/SDL.h"
#include "text.h"
#include "image.h"
#include "game.h"
#include "networkmanager.h"
#include "log.h"

bool oponenteConectado = false;

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

	//SDL_Color black = {0, 0, 0, 255};
	
	int x = 0, y = 0;
	
	
	fundo = new Image("resources/img/fundo.png");
	fundo->setPosition(0, 0);
	
	this->images["iconLogo"] = new Image("resources/img/title_small.png");
	x = (Game::Instance()->getWindow()->getWidth()) - this->images["iconLogo"]->getWidth();
	this->images["iconLogo"]->setPosition(x, 0);
	
	this->images["newGame"] = new Image("resources/img/title_new_game.png");
	x = (Game::Instance()->getWindow()->getWidth() / 2) - (this->images["newGame"]->getWidth() / 2);
	y = 75;
	this->images["newGame"]->setPosition(x, y);
	
	this->images["or"] = new Image("resources/img/text_or.png");
	
	this->buttons["createRoom"] = new MenuButton(x, y, "resources/img/createroom_button.png", "createRoom", 3, true);
	this->buttons["createRoom"]->setEventListener(this);
	this->buttons["createRoom"]->setAudioOnClick("resources/audio/fx_stab-001.wav", "playClick");
	InputHandler::getInstance()->addMouseClick(this->buttons["createRoom"]);
	
	x = (Game::Instance()->getWindow()->getWidth()) - this->buttons["createRoom"]->getWidth()/2 - 90 - this->images["or"]->getWidth()/2;
	y = (Game::Instance()->getWindow()->getHeight() / 2) - (this->images["or"]->getHeight()/2) + 20;
	this->images["or"]->setPosition(x, y);
	
	x = (Game::Instance()->getWindow()->getWidth()) - this->buttons["createRoom"]->getWidth() - 90;
	y = this->images["or"]->getY() - this->buttons["createRoom"]->getHeight() - 25;
    this->buttons["createRoom"]->setPosition(x, y);

	this->buttons["joinRoom"] = new MenuButton(x, y, "resources/img/joinroom_button.png", "joinRoom", 3, true);
	y = this->images["or"]->getY() +  this->images["or"]->getHeight() + 25;
	this->buttons["joinRoom"]->setPosition(x, y);
	this->buttons["joinRoom"]->setEventListener(this);
	this->buttons["joinRoom"]->setAudioOnClick("resources/audio/fx_stab-001.wav", "playClick");
	InputHandler::getInstance()->addMouseClick(this->buttons["joinRoom"]);
			
	this->images["imgAddress"] = new Image("resources/img/text_address.png");
	x = 80;
	y = (Game::Instance()->getWindow()->getHeight() / 2) + 50;
	this->images["imgAddress"]->setPosition(x, y);	

	this->textfields["ip"] = new TextField(x, y, 300, 30);
	x = this->images["imgAddress"]->getX() + this->images["imgAddress"]->getWidth() + 20;
	y = this->images["imgAddress"]->getY() + (this->images["imgAddress"]->getHeight() / 2) - (this->textfields["ip"]->getHeight() / 2);
	this->textfields["ip"]->setPosition(x, y);
	this->textfields["ip"]->init();
	this->textfields["ip"]->setText(NetworkManager::Instance()->getIp());
	this->textfields["ip"]->setEventListener(this);
	InputHandler::getInstance()->addMouseClick(this->textfields["ip"]);
	
	this->images["imgName"] = new Image("resources/img/text_name.png");
	y = (Game::Instance()->getWindow()->getHeight() / 2) - 50;
	this->images["imgName"]->setY(y);
	
	this->textfields["name"] = new TextField(x, y, 300, 30);
	y = this->images["imgName"]->getY() + (this->images["imgName"]->getHeight() / 2) - (this->textfields["name"]->getHeight() / 2);
	this->textfields["name"]->setPosition(x, y);
	this->textfields["name"]->init();
	this->textfields["name"]->setText(NetworkManager::Instance()->getNome());
	this->textfields["name"]->setEventListener(this);
	InputHandler::getInstance()->addMouseClick(this->textfields["name"]);
	
	x = this->textfields["name"]->getX() - this->images["imgName"]->getWidth() - 20;
	this->images["imgName"]->setX(x);

	this->buttons["menu"] = new MenuButton(x, y, "resources/img/back.png", "back", 3, true);
	y = (Game::Instance()->getWindow()->getHeight()) - (this->buttons["menu"]->getHeight());
	this->buttons["menu"]->setPosition(0, y);
	this->buttons["menu"]->setEventListener(this);
	this->buttons["menu"]->setAudioOnClick("resources/audio/fx_stab-001.wav", "playClick");
	InputHandler::getInstance()->addMouseClick(this->buttons["menu"]);
	
	this->warn = new Warn("You typed the wrong IP", "resources/img/warnok.png",
							"resources/audio/fx_stab-001.wav", "resources/font/Army.ttf");
	this->warn->init();
	this->warn->setShow(false);

	this->wait = new Warn("Waiting another player...", "resources/img/cancelButton.png",
							"resources/audio/fx_stab-001.wav", "resources/font/Army.ttf");
	this->wait->init();
	this->wait->setShow(false);
	this->wait->hideButton();

	previousTime = SDL_GetTicks();

	rend = Game::Instance()->getWindow()->getRender()->getRenderer();
    rectBackground = {0, 0, 1280, 700};
    alpha = 255;

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
    if(alpha <= 0)
    {
        velocity = 0;
    }else{
        velocity = -0.085;
    }
    
    alpha += ((SDL_GetTicks() - previousTime) / 1) * velocity;
    
    previousTime = SDL_GetTicks();
    
    if(alpha < 0)
        alpha = 0;


	if(this->warn->getShow() || this->wait->getShow())
		this->disableAllClicks();
	else
		this->enableAllClicks();
	for(map<std::string, MenuButton *>::iterator it = this->buttons.begin(); it != this->buttons.end(); it++)
		it->second->update();
	for(map<std::string, TextField *>::iterator it = this->textfields.begin(); it != this->textfields.end(); it++)
		it->second->update();
	this->warn->update();
	this->wait->update();
	
	if(oponenteConectado)
    {
    	SDL_WaitThread(threadWaitOponent, NULL);

        NetworkManager::Instance()->launchCommunication();
		Game::Instance()->getStateMachine()->changeState(new FaseState());
		oponenteConectado = false;
    }

}

void 
NetworkState::render()
{
    fundo->draw();
    for(map<std::string, Image *>::iterator it = this->images.begin(); it != this->images.end(); it++)
		it->second->draw();
	for(map<std::string, MenuButton *>::iterator it = this->buttons.begin(); it != this->buttons.end(); it++)
		it->second->draw();
	for(map<std::string, TextField *>::iterator it = this->textfields.begin(); it != this->textfields.end(); it++)
		it->second->draw();
	this->warn->draw();
	this->wait->draw();

	SDL_SetRenderDrawColor(rend, 255, 255, 255, alpha);
	SDL_RenderFillRect(rend, &rectBackground);
}

bool
NetworkState::onExit()
{
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
	for(map<std::string, Image *>::iterator it = this->images.begin(); it != this->images.end(); it++)
		delete it->second;

    delete fundo;

	SoundManager::Instance()->stopSound();
	SoundManager::Instance()->clearFromSoundManager("network", MUSIC);

	return true;
}

void 
NetworkState::enable()
{
    enableAllClicks();
}

void 
NetworkState::disable()
{
    disableAllClicks();
}

int aguardarCliente(void *ptr)
{
    map<std::string, TextField *> room = *((map<std::string, TextField *> *) ptr);
    NetworkManager::Instance()->createRoom(room["ip"]->getText(), room["name"]->getText());
    oponenteConectado = true;
    
    return 0;
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

		disable();

 		oponenteConectado = false;

		threadWaitOponent = SDL_CreateThread(aguardarCliente, "aguardarCliente", &textfields);

		this->wait->setShow(true);
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
    else if(mouseClick == this->buttons["menu"])
	{
		Game::Instance()->getStateMachine()->changeState(new MenuState());
	}
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

