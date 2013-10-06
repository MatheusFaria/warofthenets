#include "menubutton.h"
#include "sdlgameobject.h"
#include "LoaderParams.h"
#include "inputhandler.h"

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

	if(mousePosition->getX() < (position.getX() + width) &&
		mousePosition->getX() > position.getX() &&
		mousePosition->getY() < (position.getY()+height) &&
		mousePosition->getY() > (position.getY()))
	{
			currentFrame = MOUSE_OVER;

			if(InputHandler::Instance()->getMouseButtonState(LEFT))
				currentFrame = CLICKED;
	}
	else
		currentFrame = MOUSE_OUT;

	delete mousePosition;
}