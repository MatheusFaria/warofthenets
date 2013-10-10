#include "menubutton.h"
#include "sdlgameobject.h"
#include "LoaderParams.h"
#include "inputhandler.h"
#include <iostream>

using namespace std;

MenuButton::MenuButton(LoaderParams* params, void (*_callback)()):SDLGameObject(params)
,callback(_callback)
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

	//std::cout<<mousePosition->getX()<<" "<<mousePosition->getY()<<std::endl;
    
    /*
    cout << endl;
    cout << "mousePosition->getX(): " << mousePosition->getX() << endl;
    cout << "mousePosition->getY(): " << mousePosition->getY() << endl;
    
    cout << "position.getX(): " << position.getX() << endl;
    cout << "position.getY(): " << position.getY() << endl;
    */
    
	if(mousePosition->getX() < (position.getX() + width) &&
		mousePosition->getX() > position.getX() &&
		mousePosition->getY() < (position.getY()+height) &&
		mousePosition->getY() > (position.getY()))
	{
			currentFrame = MOUSE_OVER;

			//std::cout<<InputHandler::Instance()->getMouseButtonState(LEFT)<<" "<<released<<std::endl;
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
