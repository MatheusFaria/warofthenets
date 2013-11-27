#include "menustate.h"
#include "playstate.h"
#include "creditstate.h"
#include "optionstate.h"
#include "inputhandler.h"
#include "render.h"
#include "texturemanager.h"
#include "game.h"
#include "text.h"
#include "SDL2/SDL.h"
#include "soundmanager.h"
#include "gameoverstate.h"
#include <iostream>

const std::string MenuState::menuId = "MENU";

void
MenuState::update()
{

	for(int i =0; i<(int)menuObjects.size(); i++)
		menuObjects[i]->update();
}

void
MenuState::render()
{
	//std::cout<<"Drawing menu"<<std::endl;

	TextureManager::Instance()->drawFrame("fundo", 0, 0, 1280,
	 700, 0, 0, Render::getInstance()->getRenderer(), 0);

	TextureManager::Instance()->draw("title", Game::Instance()->getWindow()->getWidth()/2 - 1132/2, 10, 
		Render::getInstance()->getRenderer());

	for(int i =0; i<(int)menuObjects.size(); i++)
		menuObjects[i]->draw();
}

bool
MenuState::onEnter()
{
	
	if(!TextureManager::Instance()->loadImage("resources/img/fundo.png",
		"fundo", Render::getInstance()->getRenderer()))
	{
		std::cout<<"Error"<<std::endl;
		return false;
	}

	
	if(!TextureManager::Instance()->loadImage("resources/img/title.png",
	 "title", Render::getInstance()->getRenderer()))
	{
		return false;
	}
	
	createMenu();
	
	std::cout<<"Entering Menu State"<<std::endl;

	return true;
}

void 
MenuState::createMenu()
{

	int espacamento = 40;

	playButton = new MenuButton(0, 0, "resources/img/play.png", "playbutton", 3, true);
	int playx = (Game::Instance()->getWindow()->getWidth() / 2) - (playButton->getWidth() / 2);
	int playy= (Game::Instance()->getWindow()->getHeight() / 2) - ((playButton->getHeight()) / 2);
	playButton->setPosition(playx, playy);
	playButton->setEventListener(this);
	InputHandler::getInstance()->addMouseClick(playButton);

	
	aboutButton = new MenuButton(0, 0, "resources/img/about.png", "aboutbutton",3, true);
	int aboutx = playx;
	int abouty= (Game::Instance()->getWindow()->getHeight() / 2) + (aboutButton->getHeight() / 2) + espacamento;
	aboutButton->setPosition(aboutx, abouty);
	aboutButton->setEventListener(this);
	InputHandler::getInstance()->addMouseClick(aboutButton);

	
	exitButton = new MenuButton(0, 0, "resources/img/exit.png", "exitbutton", 3, true);
	int exitx = aboutx;
	int exity = (Game::Instance()->getWindow()->getHeight()/2) +(aboutButton->getHeight())+
		(exitButton->getHeight()/2) + espacamento*2;

	exitButton->setPosition(exitx, exity);
	exitButton->setEventListener(this);
	InputHandler::getInstance()->addMouseClick(exitButton);
	
	audioButton = new MenuButton(0, 0, "resources/img/settingsbutton.png", "config");
	int audiox = (Game::Instance()->getWindow()->getWidth()) - audioButton->getWidth() - espacamento;
	int audioy = (Game::Instance()->getWindow()->getHeight()) - audioButton->getHeight() - espacamento;
	audioButton->setPosition(audiox, audioy);
	audioButton->setEventListener(this);
	InputHandler::getInstance()->addMouseClick(audioButton);
	
	menuObjects.push_back(audioButton);
	menuObjects.push_back(playButton);
	menuObjects.push_back(aboutButton);
	menuObjects.push_back(exitButton);

}

bool 
MenuState::onExit()
{
	for(int i =0; i<(int)menuObjects.size(); i++)
		menuObjects[i]->clean();

	menuObjects.clear();

	
	TextureManager::Instance()->clearFromTextureMap("playbutton");
	TextureManager::Instance()->clearFromTextureMap("exitbutton");
	TextureManager::Instance()->clearFromTextureMap("fundo");

	SoundManager::Instance()->clearFromSoundManager("theme", MUSIC);
	
	InputHandler::getInstance()->removeMouseClick(playButton);
	InputHandler::getInstance()->removeMouseClick(aboutButton);
	InputHandler::getInstance()->removeMouseClick(exitButton);

	return true;
}

std::string 
MenuState::getStateId() const
{
	return menuId;
}

void
MenuState::menuToPlay()
{
	//Game::Instance()->getStateMachine()->pushState(new GameOverState());
	Game::Instance()->getStateMachine()->pushState(new PlayState());
}

void
MenuState::menuToCredit()
{
	Game::Instance()->getStateMachine()->pushState(new CreditState());
}


void
MenuState::exitFromMenu()
{
    //Game::Instance()->getStateMachine()->popState();
	Game::Instance()->finishGame();
}

void
MenuState::menuToOption()
{
	Game::Instance()->getStateMachine()->pushState(new OptionState());
}

void
MenuState::onMouseClick(MouseClick *mouseClick)
{
    if(mouseClick == playButton)
        menuToPlay();
    
    if(mouseClick == aboutButton)
        menuToCredit();
        
    if(mouseClick == exitButton)
        exitFromMenu();
        
    if(mouseClick == audioButton)
        menuToOption();
    
}


























