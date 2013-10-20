#include "mouseclick.h"

MouseClick::MouseClick()
{

}

MouseClick::~MouseClick()
{

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




