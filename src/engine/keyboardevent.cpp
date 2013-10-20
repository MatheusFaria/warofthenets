#include "keyboardevent.h"

KeyboardEvent::KeyboardEvent()
{

}

KeyboardEvent::~KeyboardEvent()
{

}

bool
KeyboardEvent::verifyEvent(SDL_Event sdlEvent)
{
    return KeyboardEvent::isMyEvent(sdlEvent);
}

bool
KeyboardEvent::isMyEvent(SDL_Event sdlEvent)
{
    if(sdlEvent.type == SDL_KEYDOWN)
        return true;
    else
        return false;
}




