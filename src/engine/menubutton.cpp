#include "menubutton.h"
#include "sdlgameobject.h"
#include "inputhandler.h"
#include <iostream>

using namespace std;

MenuButton::MenuButton(int _x, int _y, string _imagePath, string _imageId, void (*_callback)())
: SDLGameObject(_x, _y, 0, 0, _imagePath, _imageId), callback(_callback)
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
	Vector2D* mousePosition = InputHandler::Instance()->getMousePosition();
    
	if(mousePosition->getX() < (position.getX() + width) &&
		mousePosition->getX() > position.getX() &&
		mousePosition->getY() < (position.getY()+ height) &&
		mousePosition->getY() > (position.getY()))
	{
			currentFrame = MOUSE_OVER;

			if(InputHandler::Instance()->getMouseButtonState(LEFT) && released)
			{	
				
				currentFrame = CLICKED;

				if(callback != 0)
					callback();

				released = false;
			}	
			else if(!InputHandler::Instance()->getMouseButtonState(LEFT))
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
}

void
MenuButton::clean()
{
	
}
