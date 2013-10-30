#include "keyboard_event.h"

KeyboardEvent::KeyboardEvent()
{

}

KeyboardEvent::~KeyboardEvent()
{

}

bool
KeyboardEvent::verifyEvent(SDL_Event sdlEvent)
{
    if( (sdlEvent.type == SDL_KEYDOWN) ||
        (sdlEvent.type == SDL_KEYUP))
        return true;
    else
        return false;
}
