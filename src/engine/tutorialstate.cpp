#include "tutorialstate.h"
#include "inputhandler.h"
#include "game.h"
#include "soundmanager.h"
#include "texturemanager.h"
#include <string>

const std::string TutorialState::tutorialId = "IDTutorial";

TutorialState::TutorialState() 
{
	this->page = 1;
	this->maxPage = 4;
	this->minPage = 1;
}

bool
TutorialState::onEnter()
{
	Render * render = Render::getInstance();
	render->setColor(255, 255, 255, 255);
	render->clear();
	
	int x = 0, y = 0;

	this->buttons["next"] = new MenuButton(x, y, "resources/img/next.png", "next", 3, true);
	x = Game::Instance()->getWindow()->getWidth() - this->buttons["next"]->getWidth();
	y = Game::Instance()->getWindow()->getHeight() - this->buttons["next"]->getHeight();
	this->buttons["next"]->setPosition(x, y);
	this->buttons["next"]->setEventListener(this);
	this->buttons["next"]->setAudioOnClick("resources/audio/fx_stab-001.wav", "nextClick");
	InputHandler::getInstance()->addMouseClick(this->buttons["next"]);

	this->buttons["menu"] = new MenuButton(x, y, "resources/img/menututorial.png", "menu", 3, true);
	x = Game::Instance()->getWindow()->getWidth()/2 - this->buttons["menu"]->getWidth()/2;
	this->buttons["menu"]->setPosition(x, y);
	this->buttons["menu"]->setEventListener(this);
	this->buttons["menu"]->setAudioOnClick("resources/audio/fx_stab-001.wav", "menuClick");
	InputHandler::getInstance()->addMouseClick(this->buttons["menu"]);

	this->buttons["prev"] = new MenuButton(x, y, "resources/img/back.png", "prev", 3, true);
	x = 0;
	this->buttons["prev"]->setPosition(x, y);
	this->buttons["prev"]->setEventListener(this);
	this->buttons["prev"]->setAudioOnClick("resources/audio/fx_stab-001.wav", "prevClick");
	InputHandler::getInstance()->addMouseClick(this->buttons["prev"]);

	this->images[1] = new Image("resources/img/tutorial1.png", 0, 0, 1);
	x = Game::Instance()->getWindow()->getWidth()/2 - this->images[1]->getWidth()/2;
	y = Game::Instance()->getWindow()->getHeight()/2 - this->images[1]->getHeight()/2;
	this->images[1]->setPosition(x, y);

	this->images[2] = new Image("resources/img/tutorial2.png", 0, 0, 1);
	x = Game::Instance()->getWindow()->getWidth()/2 - this->images[2]->getWidth()/2;
	y = Game::Instance()->getWindow()->getHeight()/2 - this->images[2]->getHeight()/2;
	this->images[2]->setPosition(x, y);

	this->images[3] = new Image("resources/img/tutorial3.png", 0, 0, 1);
	x = Game::Instance()->getWindow()->getWidth()/2 - this->images[3]->getWidth()/2;
	y = Game::Instance()->getWindow()->getHeight()/2 - this->images[3]->getHeight()/2;
	this->images[3]->setPosition(x, y);

	this->images[4] = new Image("resources/img/tutorial4.png", 0, 0, 1);
	x = Game::Instance()->getWindow()->getWidth()/2 - this->images[4]->getWidth()/2;
	y = Game::Instance()->getWindow()->getHeight()/2 - this->images[4]->getHeight()/2;
	this->images[4]->setPosition(x, y);
	
	return true;
}

std::string
TutorialState::getStateId() const
{
	return TutorialState::tutorialId;
}

void 
TutorialState::update()
{
	for(map<std::string, MenuButton *>::iterator it = this->buttons.begin(); it != this->buttons.end(); it++)
		it->second->update();
}

void 
TutorialState::render()
{
	TextureManager::Instance()->drawFrame("fundo", 0, 0, 1280, 700, 0, 0, Render::getInstance()->getRenderer(), 0);
	for(map<std::string, MenuButton *>::iterator it = this->buttons.begin(); it != this->buttons.end(); it++)
		it->second->draw();
	this->images[this->page]->draw();
}

bool
TutorialState::onExit()
{
	for(map<std::string, MenuButton *>::iterator it = this->buttons.begin(); it != this->buttons.end(); it++)
	{
		InputHandler::getInstance()->removeMouseClick(it->second);
		delete it->second;
	}
	return true;
}

void 
TutorialState::onMouseClick(MouseClick *mouseClick)
{
	if(mouseClick == this->buttons["menu"])
		Game::Instance()->getStateMachine()->popState();
	else if(mouseClick == this->buttons["next"])
	{
		if(this->page < this->maxPage)
			this->page++;
	}
	else if(mouseClick == this->buttons["prev"])
	{
		if(this->page > this->minPage)
			this->page--;
	}
}

