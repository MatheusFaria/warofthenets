#include "mouse_event.h"

MouseEvent::MouseEvent()
{

}

MouseEvent::~MouseEvent()
{

}

bool
MouseEvent::verifyEvent(SDL_Event sdlEvent)
{
    return MouseEvent::isMyEvent(sdlEvent);
}

bool
MouseEvent::isMyEvent(SDL_Event sdlEvent)
{
    if( (sdlEvent.type == SDL_MOUSEBUTTONDOWN) || 
        (sdlEvent.type == SDL_MOUSEMOTION) )
        return true;
    else
        return false;
}



