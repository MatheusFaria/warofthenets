#include "inputhandler.h"
#include <cstdlib>
#include "SDL2/SDL.h"

InputHandler* InputHandler::input = NULL;

InputHandler::InputHandler()
{
	for(int i =0; i<3; i++)
		mouseButtonStates.push_back(false);

	mousePosition = new Vector2D(0, 0);
}

InputHandler::~InputHandler()
{
	mouseButtonStates.clear();
	delete mousePosition;
}

InputHandler*
InputHandler::Instance()
{
	if(input == NULL)
		input = new InputHandler();

	return input;
}

void 
InputHandler::onMouseButtonDown(SDL_Event& event)
{
	if(event.button.button == SDL_BUTTON_LEFT)
		mouseButtonStates[LEFT] = true;

	else if(event.button.button == SDL_BUTTON_RIGHT)
		mouseButtonStates[RIGHT] = true;
	
	else
		mouseButtonStates[MIDDLE] = true;
}

void 
InputHandler::onMouseButtonUp(SDL_Event& event)
{
	if(event.button.button == SDL_BUTTON_LEFT)
		mouseButtonStates[LEFT] = false;

	else if(event.button.button == SDL_BUTTON_RIGHT)
		mouseButtonStates[RIGHT] = false;
	
	else
		mouseButtonStates[MIDDLE] = false;
}

void
InputHandler::onMouseMoviment(SDL_Event& event)
{
	mousePosition->setX(event.motion.x);
	mousePosition->setY(event.motion.y);
}

void
InputHandler::update()
{
	SDL_Event event;

	switch(SDL_PollEvent(&event))
	{
		switch(event.type)
		{

			case SDL_MOUSEMOTION:
				onMouseMoviment(event);
				break;

			case SDL_MOUSEBUTTONDOWN:
				onMouseButtonDown(event);
				break;

			case SDL_MOUSEBUTTONUP:
				onMouseButtonUp(event);
				break;	
	
		}
	}
}

bool 
InputHandler::getMouseButtonState(int buttonId) const
{
	return mouseButtonStates[buttonId];
}

Vector2D* 
InputHandler::getMousePosition()
{
	return mousePosition;
}