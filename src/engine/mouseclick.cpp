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
    if((sdlEvent.type == SDL_MOUSEBUTTONDOWN) ||
        (sdlEvent.type == SDL_MOUSEBUTTONUP))
        return true;
    else
        return false;
}
