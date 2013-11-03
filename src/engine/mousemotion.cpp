#include "mousemotion.h"

MouseMotion::MouseMotion()
{

}

MouseMotion::~MouseMotion()
{

}

bool
MouseMotion::verifyEvent(SDL_Event sdlEvent)
{
    if(sdlEvent.type == SDL_MOUSEMOTION)
        return true;
    else
        return false;
}
