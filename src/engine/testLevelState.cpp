#include "testLevelState.h"
#include "hexagon.h"

#include <iostream>

using namespace std;

const string TestLevelState::menuId = "LOGO";

TestLevelState::TestLevelState(int windowWidth, int windowHeight, Render *rend)
{
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
    this->rend = rend;
    
    this->x = 0;
    this->y = 0;
}

TestLevelState::~TestLevelState()
{
    
}


void
TestLevelState::update()
{
    
}

void
TestLevelState::render()
{
    SDL_SetRenderDrawColor(rend->getRenderer(), 255, 255, 255, 255);

	hex = new Hexagon(50);
	hex->init();
	hex->setDrawColor(0, 0, 0, 255);
	hex->draw();

	for(int i = 0, j = 0, ind = 0; i < windowWidth; i+= hex->getWidth() - hex->getWidth()/4 - 2, ind++)
	{
		if(ind % 2 != 0)
			j = hex->getHeight()/2;
		else
			j = 0;
		for(; j < windowHeight; j+= hex->getHeight() -1)
		{
			rend->renderTexture(hex->generateTexture(rend->getRenderer()), i, j);
		}
	
	}
	
	list<Image *>::iterator it;
		
	for(it = listImage->begin(); it != listImage->end(); it++)
	{
	    rend->renderTexture((*it)->getTexture(), (*it)->getX(), (*it)->getY());
    }
    
	
}

bool
TestLevelState::onEnter()
{
    cout << endl;
    cout << "Pressione '1' para modo Torre" << endl;
    cout << "Pressione '2' para modo Bomba" << endl;
    cout << "Pressione '3' para modo Espiao" << endl;
    cout << endl;    
    
    
    keyboardNum = new KeyboardNum();
    keyboardNum->setEventListener(this);
    
    this->inputHandler = InputHandler::getInstance();
    inputHandler->addMouseClick(this);
    inputHandler->addKeyboardEvent(keyboardNum);
    
    this->setEventListener(this);
    
    adressImage = "resources/img/torre02.png";
    
    this->listImage = new list<Image *>();
    
	
	return true;
}

bool
TestLevelState::onExit()
{
    inputHandler->removeMouseClick(this);
    inputHandler->removeKeyboardEvent(keyboardNum);
    delete listImage;
    delete hex;
    
    return false;
}

string
TestLevelState::getStateId() const
{
    return menuId;
}

bool
TestLevelState::eventInMe(SDL_Event sdlEvent)
{
    return true;
}

void 
TestLevelState::onEvent(Event *event, SDL_Event sdlEvent)
{
    if(event == keyboardNum)
    {
        if(sdlEvent.key.keysym.sym == SDLK_1)
        {
            adressImage = "resources/img/torre02.png";
            cout << "Voce mudou para TORRE!" << endl;
        }
        if(sdlEvent.key.keysym.sym == SDLK_2)
        {
            adressImage = "resources/img/bomb01.png";
            cout << "Voce mudou para BOMBA!" << endl;
        }
        if(sdlEvent.key.keysym.sym == SDLK_3)
        {
            adressImage = "resources/img/spyunit01.png";
            cout << "Voce mudou para ESPIAO!" << endl;
        }
    }
    
    if(event == this && sdlEvent.type == SDL_MOUSEBUTTONDOWN)
    {
        int x = sdlEvent.button.x / (hex->getWidth() - hex->getWidth()/4 - 2);
        int y;
        
        if(x % 2 != 0)
            y = sdlEvent.button.y - (hex->getHeight() / 2);
        else
            y = sdlEvent.button.y;
            
        y = y / (hex->getHeight() -1);
        
        int cX = 0, cY = 0;
        int tX = 0, tY = 0;
        
        for(int i = 0, j = 0, ind = 0; (cX <= x); i+= hex->getWidth() - hex->getWidth()/4 - 2, ind++, cX++)
	    {
		    if(ind % 2 != 0)
			    j = hex->getHeight()/2;
		    else
			    j = 0;
		    
		    tX = i;
		    
		    for(; cY <= y; j+= hex->getHeight() -1, cY++)
		    {
                tY = j;
			    //rend->renderTexture(hex->generateTexture(rend->getRenderer()), i, j);
		    }
	
	    }
	    
	    if(x % 2 != 0)
	        tY += hex->getHeight()/2;
        
        Image *image = new Image();
        image->loadImage(adressImage.c_str(), rend->getRenderer());

        if(adressImage == "resources/img/torre02.png")
            tY -= hex->getHeight()/2;
        
	    image->setX(tX);
	    image->setY(tY);
	    
	    
        listImage->push_back(image);
        
    }
    
    
}












