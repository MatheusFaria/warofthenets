#include "configurationstate.h"
#include "playstate.h"
#include "fasestate.h"
#include "inputhandler.h"
#include "text.h"
#include "image.h"
#include "game.h"
#include "soundmanager.h"
#include <string>

const std::string ConfigurationState::configurationId = "IDConfiguration";

int ConfigurationState::soundVolume = 10;
int ConfigurationState::effectsVolume = 10;

ConfigurationState::ConfigurationState() 
{
}

bool
ConfigurationState::onEnter()
{
	Render * render = Render::getInstance();
	render->setColor(255, 255, 255, 255);
	render->clear();

	SDL_Color black = {0, 0, 0, 255};

	this->texts["title"] = new Text("Settings", 80);
	this->texts["title"]->setFont("resources/font/Army.ttf");
	this->texts["title"]->setColor(black);

	int x = (Game::Instance()->getWindow()->getWidth() / 2) - (this->texts["title"]->getWidth() / 2);
	int y = 50;
	this->texts["title"]->setPosition(x, y);

	y += this->texts["title"]->getHeight() + 100;

	this->texts["sound"] = new Text("Sound volume:", 50);
	this->texts["sound"]->setFont("resources/font/Army.ttf");
	this->texts["sound"]->setColor(black);
	x = (Game::Instance()->getWindow()->getWidth() / 4) - (this->texts["sound"]->getWidth() / 2);
	y += this->texts["sound"]->getHeight()*2;
	this->texts["sound"]->setPosition(x, y);

	this->texts["soundValue"] = new Text(std::to_string(ConfigurationState::soundVolume), 50);
	this->texts["soundValue"]->setFont("resources/font/Army.ttf");
	this->texts["soundValue"]->setColor(black);
	x += this->texts["sound"]->getWidth() + 40;
	this->texts["soundValue"]->setPosition(x, y);

	this->buttons["soundUp"] = new MenuButton(x, y, "resources/img/up.png", "soundUp", 3, true);
	y -= this->buttons["soundUp"]->getHeight()/2;
	x = this->texts["sound"]->getWidth()*1.7;
	this->buttons["soundUp"]->setPosition(x, y);
	this->buttons["soundUp"]->setEventListener(this);
	this->buttons["soundUp"]->setAudioOnClick("resources/audio/fx_stab-001.wav", "playClick");
	InputHandler::getInstance()->addMouseClick(this->buttons["soundUp"]);

	this->buttons["soundDown"] = new MenuButton(x, y, "resources/img/down.png", "soundDown", 3, true);
	y += this->buttons["soundUp"]->getHeight() + 1;
	this->buttons["soundDown"]->setPosition(x, y);
	this->buttons["soundDown"]->setEventListener(this);
	this->buttons["soundDown"]->setAudioOnClick("resources/audio/fx_stab-001.wav", "playClick");
	InputHandler::getInstance()->addMouseClick(this->buttons["soundDown"]);

	this->texts["effect"] = new Text("Effect volume:", 50);
	this->texts["effect"]->setFont("resources/font/Army.ttf");
	this->texts["effect"]->setColor(black);
	x = (Game::Instance()->getWindow()->getWidth() / 4) - (this->texts["sound"]->getWidth() / 2);
	y = this->texts["sound"]->getY()*1.5;
	this->texts["effect"]->setPosition(x, y);

	this->texts["effectValue"] = new Text(std::to_string(ConfigurationState::effectsVolume), 50);
	this->texts["effectValue"]->setFont("resources/font/Army.ttf");
	this->texts["effectValue"]->setColor(black);
	x += this->texts["effect"]->getWidth() + 20;
	this->texts["effectValue"]->setPosition(x, y);

	this->buttons["effectUp"] = new MenuButton(x, y, "resources/img/up.png", "effectUp", 3, true);
	y -= this->buttons["effectUp"]->getHeight()/2;
	x = this->texts["sound"]->getWidth()*1.7;
	this->buttons["effectUp"]->setPosition(x, y);
	this->buttons["effectUp"]->setEventListener(this);
	this->buttons["effectUp"]->setAudioOnClick("resources/audio/fx_stab-001.wav", "playClick");
	InputHandler::getInstance()->addMouseClick(this->buttons["effectUp"]);

	this->buttons["effectDown"] = new MenuButton(x, y, "resources/img/down.png", "effectDown", 3, true);
	y += this->buttons["effectUp"]->getHeight() + 1;
	this->buttons["effectDown"]->setPosition(x, y);
	this->buttons["effectDown"]->setEventListener(this);
	this->buttons["effectDown"]->setAudioOnClick("resources/audio/fx_stab-001.wav", "playClick");
	InputHandler::getInstance()->addMouseClick(this->buttons["effectDown"]);

	this->buttons["menu"] = new MenuButton(x, y, "resources/img/menubutton.png", "menu", 3, true);
	x = Game::Instance()->getWindow()->getWidth() - this->buttons["menu"]->getWidth() - 30;
	y = Game::Instance()->getWindow()->getHeight() - this->buttons["menu"]->getHeight() - 30;
	this->buttons["menu"]->setPosition(x, y);
	this->buttons["menu"]->setEventListener(this);
	this->buttons["menu"]->setAudioOnClick("resources/audio/fx_stab-001.wav", "playClick");
	InputHandler::getInstance()->addMouseClick(this->buttons["menu"]);

	return true;
}

std::string
ConfigurationState::getStateId() const
{
	return ConfigurationState::configurationId;
}

void 
ConfigurationState::update()
{
	for(map<std::string, MenuButton *>::iterator it = this->buttons.begin(); it != this->buttons.end(); it++)
		it->second->update();
}

void 
ConfigurationState::render()
{
	for(map<std::string, Text *>::iterator it = this->texts.begin(); it != this->texts.end(); it++)
		it->second->draw();
	for(map<std::string, MenuButton *>::iterator it = this->buttons.begin(); it != this->buttons.end(); it++)
		it->second->draw();
}

bool
ConfigurationState::onExit()
{
	for(map<std::string, Text *>::iterator it = this->texts.begin(); it != this->texts.end(); it++)
		delete it->second;
	for(map<std::string, MenuButton *>::iterator it = this->buttons.begin(); it != this->buttons.end(); it++)
	{
		InputHandler::getInstance()->removeMouseClick(it->second);
		delete it->second;
	}
	return true;
}

void 
ConfigurationState::onMouseClick(MouseClick *mouseClick)
{
	if(mouseClick == this->buttons["menu"])
		Game::Instance()->getStateMachine()->popState();
	else if(mouseClick == this->buttons["soundUp"])
	{
		if(ConfigurationState::soundVolume < 10)
		{
			ConfigurationState::soundVolume++;
			SoundManager::Instance()->setVolumeSound(ConfigurationState::soundVolume);
			this->texts["soundValue"]->setValue(std::to_string(ConfigurationState::soundVolume));
		}
	}
	else if(mouseClick == this->buttons["soundDown"])
	{
		if(ConfigurationState::soundVolume > 0)
		{
			ConfigurationState::soundVolume--;
			SoundManager::Instance()->setVolumeSound(ConfigurationState::soundVolume);
			this->texts["soundValue"]->setValue(std::to_string(ConfigurationState::soundVolume));
		}
	}
	else if(mouseClick == this->buttons["effectUp"])
	{
		if(ConfigurationState::effectsVolume < 10)
		{
			ConfigurationState::effectsVolume++;
			SoundManager::Instance()->setVolumeEffect(ConfigurationState::effectsVolume);
			this->texts["effectValue"]->setValue(std::to_string(ConfigurationState::effectsVolume));
		}
	}
	else if(mouseClick == this->buttons["effectDown"])
	{
		if(ConfigurationState::effectsVolume > 0)
		{
			ConfigurationState::effectsVolume--;
			SoundManager::Instance()->setVolumeEffect(ConfigurationState::effectsVolume);
			this->texts["effectValue"]->setValue(std::to_string(ConfigurationState::effectsVolume));
		}
	}
}

