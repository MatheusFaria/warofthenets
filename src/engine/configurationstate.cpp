#include "configurationstate.h"
#include "playstate.h"
#include "fasestate.h"
#include "inputhandler.h"
#include "text.h"
#include "image.h"
#include "game.h"
#include "soundmanager.h"
#include "texturemanager.h"
#include <string>

#include <iostream>
using namespace std;

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

	SDL_Color white = {255, 255, 255, 255};

	int x = 0, y = 0;

    //this->images["fundo"] = new Image("resources/img/fundo.png");
	//this->images["fundo"]->setPosition(0, 0);
	
	this->images["iconLogo"] = new Image("resources/img/title_small.png");
	x = (Game::Instance()->getWindow()->getWidth()) - this->images["iconLogo"]->getWidth();
	this->images["iconLogo"]->setPosition(x, 0);
	
	this->images["titleSettings"] = new Image("resources/img/title_settings.png");
	x = (Game::Instance()->getWindow()->getWidth() / 2) - (this->images["titleSettings"]->getWidth() / 2);
	y = 75;
	this->images["titleSettings"]->setPosition(x, y);

    this->images["sound"] = new Image("resources/img/text_sound_volume.png");
    x = 50;
    y = (Game::Instance()->getWindow()->getHeight()/2) - (this->images["sound"]->getHeight()/2) - 50;
	this->images["sound"]->setPosition(x, y);

	this->texts["soundValue"] = new Text(std::to_string(ConfigurationState::soundVolume), 55);
	this->texts["soundValue"]->setFont("resources/font/Army.ttf");
	this->texts["soundValue"]->setColor(white);
	x = this->images["sound"]->getX() + this->images["sound"]->getWidth() + 20;
	y = this->images["sound"]->getY() + (this->images["sound"]->getHeight()/2) - (this->texts["soundValue"]->getHeight()/2);
	this->texts["soundValue"]->setPosition(x, y);

    
	this->buttons["soundUp"] = new MenuButton(x, y, "resources/img/up.png", "soundUp", 3, true);
	x = this->texts["soundValue"]->getX() + this->texts["soundValue"]->getWidth() + 15;
	y = this->images["sound"]->getY() + (this->images["sound"]->getHeight()/2) - (this->texts["soundValue"]->getHeight()) - 2;
	this->buttons["soundUp"]->setPosition(x, y);
	this->buttons["soundUp"]->setEventListener(this);
	this->buttons["soundUp"]->setAudioOnClick("resources/audio/fx_stab-001.wav", "playClick");
	InputHandler::getInstance()->addMouseClick(this->buttons["soundUp"]);

	this->buttons["soundDown"] = new MenuButton(x, y, "resources/img/down.png", "soundDown", 3, true);
	x = this->texts["soundValue"]->getX() + this->texts["soundValue"]->getWidth() + 15;
	y = this->images["sound"]->getY() + (this->images["sound"]->getHeight()/2) + 2;
	this->buttons["soundDown"]->setPosition(x, y);
	this->buttons["soundDown"]->setEventListener(this);
	this->buttons["soundDown"]->setAudioOnClick("resources/audio/fx_stab-001.wav", "playClick");
	InputHandler::getInstance()->addMouseClick(this->buttons["soundDown"]);

    this->images["effect"] = new Image("resources/img/text_effect_volume.png");
    x = 50;
    y = (Game::Instance()->getWindow()->getHeight()/2) - (this->images["effect"]->getHeight()/2) + 150;
	this->images["effect"]->setPosition(x, y);

	this->texts["effectValue"] = new Text(std::to_string(ConfigurationState::effectsVolume), 55);
	this->texts["effectValue"]->setFont("resources/font/Army.ttf");
	this->texts["effectValue"]->setColor(white);
	x = this->images["effect"]->getX() + this->images["effect"]->getWidth() + 20;
	y = this->images["effect"]->getY() + (this->images["effect"]->getHeight()/2) - (this->texts["soundValue"]->getHeight()/2);
	this->texts["effectValue"]->setPosition(x, y);

	this->buttons["effectUp"] = new MenuButton(x, y, "resources/img/up.png", "effectUp", 3, true);
	x = this->texts["effectValue"]->getX() + this->texts["effectValue"]->getWidth() + 15;
	y = this->images["effect"]->getY() + (this->images["effect"]->getHeight()/2) - (this->texts["effectValue"]->getHeight()) - 2;
	this->buttons["effectUp"]->setPosition(x, y);
	this->buttons["effectUp"]->setEventListener(this);
	this->buttons["effectUp"]->setAudioOnClick("resources/audio/fx_stab-001.wav", "playClick");
	InputHandler::getInstance()->addMouseClick(this->buttons["effectUp"]);

	this->buttons["effectDown"] = new MenuButton(x, y, "resources/img/down.png", "effectDown", 3, true);
	x = this->texts["effectValue"]->getX() + this->texts["effectValue"]->getWidth() + 15;
	y = this->images["effect"]->getY() + (this->images["effect"]->getHeight()/2) + 2;
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

void 
ConfigurationState::enable()
{
    for(map<std::string, MenuButton *>::iterator it = this->buttons.begin(); it != this->buttons.end(); it++)
		it->second->setActive(true);
}
void 
ConfigurationState::disable()
{
    for(map<std::string, MenuButton *>::iterator it = this->buttons.begin(); it != this->buttons.end(); it++)
		it->second->setActive(false);
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
	TextureManager::Instance()->drawFrame("fundo", 0, 0, 1280, 700, 0, 0, Render::getInstance()->getRenderer(), 0);
	for(map<std::string, Image *>::iterator it = this->images.begin(); it != this->images.end(); it++)
		it->second->draw();
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
	for(map<std::string, Image *>::iterator it = this->images.begin(); it != this->images.end(); it++)
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

