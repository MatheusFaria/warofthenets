#include "mouse_motion.h"

MouseMotion::MouseMotion()
{

}

MouseMotion::~MouseMotion()
{

}

bool
MouseMotion::verifyEvent(SDL_Event sdlEvent)
{
    return MouseMotion::isMyEvent(sdlEvent);
}

bool
MouseMotion::isMyEvent(SDL_Event sdlEvent)
{
    if(sdlEvent.type == SDL_MOUSEMOTION)
        return true;
    else
        return false;
}


