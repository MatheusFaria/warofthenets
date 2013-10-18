#include "inputhandler.h"
#include <cstdlib>
#include "SDL2/SDL.h"
#include <iostream>

InputHandler* InputHandler::input = NULL;

InputHandler::InputHandler()
{
	for(int i =0; i<3; i++)
		mouseButtonStates.push_back(false);

	mousePosition = new Vector2D();
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

	if(event.button.button == SDL_BUTTON_RIGHT)
		mouseButtonStates[RIGHT] = true;
	
	if(event.button.button == SDL_BUTTON_MIDDLE)
		mouseButtonStates[MIDDLE] = true;
}

void 
InputHandler::onMouseButtonUp(SDL_Event& event)
{
	if(event.button.button == SDL_BUTTON_LEFT)
		mouseButtonStates[LEFT] = false;

	if(event.button.button == SDL_BUTTON_RIGHT)
		mouseButtonStates[RIGHT] = false;
	
	if(event.button.button == SDL_BUTTON_MIDDLE)
		mouseButtonStates[MIDDLE] = false;
}

void
InputHandler::onMouseMoviment(SDL_Event& event)
{
	mousePosition->setX(event.motion.x);
	mousePosition->setY(event.motion.y);
}

void
InputHandler::update(SDL_Event event)
{
	switch(event.type)
	{
		case SDL_MOUSEMOTION:
			//std::cout<<"Entrou aqui"<<std::endl;
			onMouseMoviment(event);
			break;

		case SDL_MOUSEBUTTONDOWN:
			std::cout<<"Entrou aqui"<<std::endl;
			onMouseButtonDown(event);
			break;

		case SDL_MOUSEBUTTONUP:
			//std::cout<<"Entrou aqui"<<std::endl;
			onMouseButtonUp(event);
			break;	

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
