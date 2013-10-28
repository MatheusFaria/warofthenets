#include "menubutton.h"
#include "sdlgameobject.h"
#include "inputhandler.h"
#include "SDL2/SDL.h"
#include <iostream>

using namespace std;

MenuButton::MenuButton(int _x, int _y, string _imagePath, string _imageId)
: SDLGameObject(_x, _y, 0, 0, _imagePath, _imageId), MouseClick()
{
	currentFrame = MOUSE_OUT;
	released = true;
}

void
MenuButton::draw()
{
	SDLGameObject::draw();
}

void
MenuButton::update()
{    
	Vector2D mousePosition(sdlEvent.motion.x, sdlEvent.motion.y);
	
	if(mousePosition.getX() < (position.getX() + width) &&
		mousePosition.getX() > position.getX() &&
		mousePosition.getY() < (position.getY()+ height) &&
		mousePosition.getY() > (position.getY()))
	{
	
        currentFrame = MOUSE_OVER;

        if( (sdlEvent.button.button == SDL_BUTTON_LEFT)  )
		//if(InputHandler::Instance()->getMouseButtonState(LEFT) && released)
		{	
			
			currentFrame = CLICKED;

			released = false;
		}
		if( (sdlEvent.button.button == SDL_BUTTON_LEFT) &&
            (sdlEvent.button.state == SDL_RELEASED) )
		//else if(!InputHandler::Instance()->getMouseButtonState(LEFT))
   		{
        	released = true;
        	currentFrame = MOUSE_OVER;
    	}
	}
	else
	{
		released = true;
		currentFrame = MOUSE_OUT;
	}	
	
	//cout << "released: " << released << endl;
}

void
MenuButton::clean()
{
	
}


bool
MenuButton::verifyEvent(SDL_Event sdlEvent)
{
    this->sdlEvent = sdlEvent;
    
    if(sdlEvent.button.button == SDL_BUTTON_LEFT)
    {
        return true;
    }
}


bool
MenuButton::eventInMe(SDL_Event sdlEvent)
{
    if( (sdlEvent.button.x > this->getX()) &&
        (sdlEvent.button.x < (this->getX() + this->getWidth())) &&
        (sdlEvent.button.y > this->getY()) && 
        (sdlEvent.button.y < (this->getY() + this->getHeight())))
    {
        if( (sdlEvent.button.button == SDL_BUTTON_LEFT) &&
            (sdlEvent.button.state == SDL_RELEASED) &&
            !released)
            return true;
    }
    
    return false;
}




























