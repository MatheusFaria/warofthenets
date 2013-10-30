#include "mouseevent.h"

MouseEvent::MouseEvent()
{

}

MouseEvent::~MouseEvent()
{

}

bool
MouseEvent::verifyEvent(SDL_Event sdlEvent)
{
    if( (sdlEvent.type == SDL_MOUSEBUTTONDOWN) ||
        (sdlEvent.type == SDL_MOUSEBUTTONUP) ||
        (sdlEvent.type == SDL_MOUSEMOTION) )
        return true;
    else
        return false;
}
