#include "event.h"

//#include <iostream>
//using namespace std;

Event::Event()
{
    //cout << "Event instanciado!" << endl;
    this->active = true;
}

Event::~Event()
{
    //cout << "Event destruido!" << endl;
}

void 
Event::notifyListener(SDL_Event sdlEvent)
{
	if(eventListener != NULL)
		eventListener->onEvent(this, sdlEvent);
}

bool
Event::isActive()
{
    return active;
}

void
Event::setActive(bool active)
{
    this->active = active;
}

bool
Event::verifyEvent(SDL_Event sdlEvent)
{
    if( (sdlEvent.type == SDL_KEYDOWN) ||
        (sdlEvent.type == SDL_KEYUP) ||
        (sdlEvent.type == SDL_MOUSEBUTTONDOWN) ||
        (sdlEvent.type == SDL_MOUSEBUTTONUP) || 
        (sdlEvent.type == SDL_MOUSEMOTION) )
        return true;
    else
        return false;
}

bool
Event::sendMeToListener(SDL_Event sdlEvent)
{
    if(active)
    {
        if(verifyEvent(sdlEvent))
        {
	        if(eventInMe(sdlEvent))
	        {
		        notifyListener(sdlEvent);
	            return true;
	        }
        }
    }
    
    return false;
}


Event::EventListener *
Event::getEventListener()
{
	return eventListener;
}

void
Event::setEventListener(EventListener *eventListener)
{
	this->eventListener = eventListener;
}






































