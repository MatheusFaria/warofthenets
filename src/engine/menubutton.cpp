#include "menubutton.h"
#include "sdlgameobject.h"
#include "LoaderParams.h"
#include "inputhandler.h"
#include <iostream>

MenuButton::MenuButton(LoaderParams* params):SDLGameObject(params)
{
	currentFrame = MOUSE_OUT;
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

	if(mousePosition->getX() < (position.getX() + width) &&
		mousePosition->getX() > position.getX() &&
		mousePosition->getY() < (position.getY()+height) &&
		mousePosition->getY() > (position.getY()))
	{
			currentFrame = MOUSE_OVER;

			if(InputHandler::Instance()->getMouseButtonState(LEFT))
			{	
				//std::cout<<"Clicou em mim"<<std::endl;
				currentFrame = CLICKED;
			}	
	}
	else
		currentFrame = MOUSE_OUT;

}

void
MenuButton::clean()
{
	
}