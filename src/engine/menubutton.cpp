#include "menubutton.h"
#include "sdlgameobject.h"
#include "inputhandler.h"
#include "texturemanager.h"
#include "render.h"
#include "soundmanager.h"
#include "SDL2/SDL.h"
#include <iostream>

using namespace std;

MenuButton::MenuButton(int _x, int _y, string _imagePath, string _imageId, int _numFrames, bool _animate)
: SDLGameObject(_x, _y, 0, 0, _imagePath, _imageId, _numFrames), MouseClick()
{
	currentFrame = MOUSE_OUT;
	currentRow = MOUSE_OUT;
	released = true;
	animate = _animate;
	soundId = "";
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
	
	if(mousePosition.getX() < (position.getX() + getWidth()) &&
		mousePosition.getX() > position.getX() &&
		mousePosition.getY() < (position.getY()+ getHeight()) &&
		mousePosition.getY() > (position.getY()))
	{
		if(animate)
        	currentRow = MOUSE_OVER;

        if( (sdlEvent.button.button == SDL_BUTTON_LEFT)  )
		//if(InputHandler::Instance()->getMouseButtonState(LEFT) && released)
		{	
			if(animate)
				currentRow = CLICKED;

			released = false;
		}
		if( (sdlEvent.button.button == SDL_BUTTON_LEFT) &&
            (sdlEvent.button.state == SDL_RELEASED) )
		//else if(!InputHandler::Instance()->getMouseButtonState(LEFT))
   		{
        	released = true;
        	
        	if(animate)
        		currentRow = MOUSE_OVER;
    	}
	}
	else
	{
		released = true;

		if(animate)
			currentRow = MOUSE_OUT;
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
    
    //Lembrar do "!released";

    if( (sdlEvent.button.button == SDL_BUTTON_LEFT) &&
        (sdlEvent.button.state == SDL_RELEASED) &&
        (sdlEvent.type != SDL_MOUSEMOTION) /*&&
        !released*/)
    {
        return true;
    }

    return false;
}


bool
MenuButton::eventInMe(SDL_Event sdlEvent)
{
    if( (sdlEvent.button.x > this->getX()) &&
        (sdlEvent.button.x < (this->getX() + this->getWidth())) &&
        (sdlEvent.button.y > this->getY()) && 
        (sdlEvent.button.y < (this->getY() + this->getHeight())))
    {
            return true;
    }
    
    return false;
}

bool
MenuButton::setAudioOnClick(string path, string soundId)
{
	this->soundId = soundId;
	SoundManager::Instance()->loadSound(path, soundId, SFX);

	return true;
}

bool
MenuButton::playSoundOnClick()
{
	if(soundId != "")
	{	
		SoundManager::Instance()->playSound(soundId, 0);
		return true;
	}
	
	return false;	
}


























