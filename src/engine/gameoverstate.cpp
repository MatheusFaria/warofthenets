#include "gameoverstate.h"
#include "game.h"
#include "texturemanager.h"
#include "networkstate.h"
#include "inputhandler.h"
#include "image.h"
#include "SDL2/SDL.h"
#include "playstate.h"
#include "menustate.h"
#include <iostream>

const std::string GameOverState::gameOverId = "GAMEOVER";

void
GameOverState::update()
{
	for(int i =0; i<(int)gameOverObjects.size(); i++)
		gameOverObjects[i]->update();
	
	                                                                                                                                                                              
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
    
}

void
GameOverState::render()
{
	for(int i =0; i<(int)gameOverObjects.size(); i++)
		gameOverObjects[i]->draw();
	
	SDL_SetRenderDrawColor(rend, 255, 255, 255, alpha);
	SDL_RenderFillRect(rend, &rectBackground);
}

bool
GameOverState::onEnter()
{
    background = new Image("resources/img/fundo.png");
    
    title = new Image("resources/img/gameover.png");
    int titleX = (Game::Instance()->getWindow()->getWidth() / 2) - (title->getWidth() / 2);
	int titleY = 50;
	title->setPosition(titleX, titleY);

    newGame = new MenuButton(0, 0, "resources/img/newgame.png", "newGame");
	int newGameX = (Game::Instance()->getWindow()->getWidth() / 2) - (newGame->getWidth() / 2);
	int newGameY= (Game::Instance()->getWindow()->getHeight() / 2) - (newGame->getHeight() / 2);
	newGame->setPosition(newGameX, newGameY);
	newGame->setEventListener(this);
	InputHandler::getInstance()->addMouseClick(newGame);

    quitToMenu = new MenuButton(0, 0, "resources/img/quittomenu.png", "quitToMenu");
	int quitToMenuX = (Game::Instance()->getWindow()->getWidth() / 2) - (quitToMenu->getWidth() / 2);
	int quitToMenuY= (Game::Instance()->getWindow()->getHeight() / 2) + (quitToMenu->getHeight() / 2) + 20;
	quitToMenu->setPosition(quitToMenuX, quitToMenuY);
	quitToMenu->setEventListener(this);
	InputHandler::getInstance()->addMouseClick(quitToMenu);
    
    gameOverObjects.push_back(background);
    gameOverObjects.push_back(title);
    gameOverObjects.push_back(newGame);
    gameOverObjects.push_back(quitToMenu);
    
    InputHandler::getInstance()->addKeyboardEvent(this);
    
    previousTime = SDL_GetTicks();
    
	rend = Game::Instance()->getWindow()->getRender()->getRenderer();
    rectBackground = {0, 0, 1280, 700};
    alpha = 255;
    
	return true;
}

bool
GameOverState::onExit()
{    
    InputHandler::getInstance()->removeKeyboardEvent(this);
    InputHandler::getInstance()->removeMouseClick(quitToMenu);
    InputHandler::getInstance()->removeMouseClick(newGame);
    
    quitToMenu->clean();
    newGame->clean();
    title->clean();
    background->clean();
    
    delete quitToMenu;
    delete newGame;
    delete title;
    delete background;
    
	//std::cout<<"Exiting Game Over State"<<std::endl;
	return true;
}

void 
GameOverState::enable()
{
    newGame->setActive(true);
    quitToMenu->setActive(true);
}
void 
GameOverState::disable()
{
    newGame->setActive(false);
    quitToMenu->setActive(false);
}

std::string 
GameOverState::getStateId() const
{
	return gameOverId;
}

bool 
GameOverState::eventInMe(SDL_Event sdlEvent)
{
	if(sdlEvent.key.keysym.sym == SDLK_ESCAPE){
		Game::Instance()->getStateMachine()->popState();
		return true;
	}

	return false;
}

void
GameOverState::onMouseClick(MouseClick *mouseClick)
{
    if(mouseClick == quitToMenu)
        Game::Instance()->getStateMachine()->pushState(new MenuState());
        
    if(mouseClick == newGame)
        Game::Instance()->getStateMachine()->changeState(new NetworkState());
}
