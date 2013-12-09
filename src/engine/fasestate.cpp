#include "fasestate.h"
#include "playstate.h"
#include "game.h"
#include "inputhandler.h"
#include "soundmanager.h"
#include "networkmanager.h"

const std::string FaseState::faseId = "MENU";

void
FaseState::update()
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

	for(int i = 0; i < (int)vectorButtons.size(); i++)
		vectorButtons[i]->update();
	
	if(NetworkManager::Instance()->getTipo() == 0)
	    receberMensagens();
}

void
FaseState::render()
{
	
	for(int i = 0; i < (int)vectorButtons.size(); i++)
		vectorButtons[i]->draw();
		
	imgTitulo->draw();

	SDL_SetRenderDrawColor(rend, 190, 190, 190, alpha);
	SDL_RenderFillRect(rend, &rectBackground);
}

bool
FaseState::onEnter()
{

	SoundManager::Instance()->loadSound("resources/audio/Black_Vortex.ogg", "stage", MUSIC);
	SoundManager::Instance()->playMusic("stage", -1);

    imgTitulo = new Image("resources/img/titulofase.png", 0, 0);
    int imgTituloX = (Game::Instance()->getWindow()->getWidth() / 2) - (imgTitulo->getWidth() / 2);
	int imgTituloY = 10;
    imgTitulo->setPosition(imgTituloX, imgTituloY);
    
	btnBrasil = new MenuButton(0, 0, "resources/img/level1.png", "level1", 3, true);
	int btnBrasilX = (Game::Instance()->getWindow()->getWidth() / 2) - (btnBrasil->getWidth() / 2);
	int btnBrasilY = (Game::Instance()->getWindow()->getHeight() / 2) - (btnBrasil->getHeight() * 1);
	btnBrasil->setPosition(btnBrasilX, btnBrasilY);
	btnBrasil->setEventListener(this);
	InputHandler::getInstance()->addMouseClick(btnBrasil);
	
	btnAlemanha = new MenuButton(0, 0, "resources/img/level2.png", "level2", 3, true);
	int btnAlemanhaX = btnBrasilX - (3 * btnAlemanha->getWidth() / 2);
	int btnAlemanhaY = btnBrasilY;
	btnAlemanha->setPosition(btnAlemanhaX, btnAlemanhaY);
	btnAlemanha->setEventListener(this);
	InputHandler::getInstance()->addMouseClick(btnAlemanha);
	
	btnJapao = new MenuButton(0, 0, "resources/img/level4.png", "level4", 3, true);
	int btnJapaoX = btnBrasilX + (3 * btnJapao->getWidth() / 2);
	int btnJapaoY = btnBrasilY;
	btnJapao->setPosition(btnJapaoX, btnJapaoY);
	btnJapao->setEventListener(this);
	InputHandler::getInstance()->addMouseClick(btnJapao);
	
	btnIndia = new MenuButton(0, 0, "resources/img/level5.png", "level5", 3, true);
	int btnIndiaX = btnBrasilX - btnIndia->getWidth();
	int btnIndiaY = (Game::Instance()->getWindow()->getHeight() / 2) + (btnIndia->getHeight() * 1);
	btnIndia->setPosition(btnIndiaX, btnIndiaY);
	btnIndia->setEventListener(this);
	InputHandler::getInstance()->addMouseClick(btnIndia);
	
	btnRussia = new MenuButton(0, 0, "resources/img/level3.png", "level3", 3, true);
	int btnRussiaX = btnBrasilX + btnIndia->getWidth();
	int btnRussiaY = (Game::Instance()->getWindow()->getHeight() / 2) + (btnRussia->getHeight() * 1);
	btnRussia->setPosition(btnRussiaX, btnRussiaY);
	btnRussia->setEventListener(this);
	InputHandler::getInstance()->addMouseClick(btnRussia);
	
	vectorButtons.push_back(btnBrasil);
	vectorButtons.push_back(btnAlemanha);
	vectorButtons.push_back(btnJapao);
	vectorButtons.push_back(btnIndia);
	vectorButtons.push_back(btnRussia);
	
	if(NetworkManager::Instance()->getTipo() == 0)
		InputHandler::getInstance()->setActive(false);
	
	previousTime = SDL_GetTicks();

	rend = Game::Instance()->getWindow()->getRender()->getRenderer();
    rectBackground = {0, 0, 1280, 700};
    alpha = 255;

	return true;
}

bool 
FaseState::onExit()
{
	for(int i = 0; i < (int)vectorButtons.size(); i++)
	{
		InputHandler::getInstance()->removeMouseClick(vectorButtons[i]);
		vectorButtons[i]->clean();
		delete vectorButtons[i];
    }
    
	vectorButtons.clear();
	
	delete imgTitulo;

	SoundManager::Instance()->stopSound();
	SoundManager::Instance()->clearFromSoundManager("stage", MUSIC);

	return true;
}

void  
FaseState::enable()
{
    btnBrasil->setActive(true);
    btnAlemanha->setActive(true);
    btnJapao->setActive(true);
    btnIndia->setActive(true);
    btnRussia->setActive(true);
}

void  
FaseState::disable()
{
    btnBrasil->setActive(false);
    btnAlemanha->setActive(false);
    btnJapao->setActive(false);
    btnIndia->setActive(false);
    btnRussia->setActive(false);
}


std::string 
FaseState::getStateId() const
{
	return faseId;
}

void  
FaseState::setEnableButtons(bool enable)
{
    for(int i = 0; i < (int)vectorButtons.size(); i++)
        vectorButtons[i]->setActive(enable);
}

void
FaseState::onMouseClick(MouseClick *mouseClick)
{
    if(mouseClick == btnBrasil)
        enviarIniciarFase("1");
    
    if(mouseClick == btnAlemanha)
        enviarIniciarFase("2");
        
    if(mouseClick == btnJapao)
        enviarIniciarFase("4");
    
    if(mouseClick == btnIndia)
        enviarIniciarFase("5");

    if(mouseClick == btnRussia)
        enviarIniciarFase("3");
}

void 
FaseState::iniciarFase(string nomeFase)
{
    for(int i = 0; i < (int)vectorButtons.size(); i++)
	{
		InputHandler::getInstance()->removeMouseClick(vectorButtons[i]);
	}
    Game::Instance()->getStateMachine()->pushState(new PlayState(nomeFase));
}

void 
FaseState::enviarIniciarFase(string nomeFase)
{
    if(!faseValida(nomeFase))
        return;

    Data data;

	data.type = atoi(nomeFase.c_str());

	NetworkManager::Instance()->sendMessage(data);
	
	iniciarFase(nomeFase);
}

void
FaseState::receberMensagens()
{
	Data data;

	while(true)
	{
		data = NetworkManager::Instance()->receiveMessage();

		if(data.type == -1)
		{
			break;
        }
        else if(faseValida(std::to_string(data.type))) 
        {
		    iniciarFase(std::to_string(data.type));
		    InputHandler::getInstance()->setActive(true);
	    }
		
		//if(data.type == DISCONECTED)
		//    break;
	}
}

bool 
FaseState::faseValida(string nomeFase)
{
    if( nomeFase == "1" || nomeFase == "2" || nomeFase == "3" ||
        nomeFase == "4" || nomeFase == "5")
        return true;
    else
        return false;
}
