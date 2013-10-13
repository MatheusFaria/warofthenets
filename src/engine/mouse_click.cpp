#include "mouse_click.h"
#include "input_handler.h"

MouseClick::MouseClick()
{
    InputHandler *inputHandler = InputHandler::getInstance();
    inputHandler->addMouseClick(this);
}

MouseClick::~MouseClick()
{
    InputHandler *inputHandler = InputHandler::getInstance();
    inputHandler->removeMouseClick(this);
}

bool
MouseClick::verifyEvent(SDL_Event sdlEvent)
{
    return MouseClick::isMyEvent(sdlEvent);
}

bool
MouseClick::isMyEvent(SDL_Event sdlEvent)
{
    if(sdlEvent.type == SDL_MOUSEBUTTONDOWN)
        return true;
    else
        return false;
}




