#include "event.h"

//#include <iostream>
//using namespace std;

Event::Event()
{
    //cout << "Event instanciado!" << endl;
    this->active = true;
    this->eventListener = NULL;
}

Event::~Event()
{
    //cout << "Event destruido!" << endl;
}

void 
Event::notifyListener()
{
	if(eventListener != NULL)
		eventListener->onEvent(this);
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
Event::sendMeToListener(SDL_Event event)
{
    if(active)
    {
        if(verifyEvent(event))
        {
	        if(eventInMe(event))
	        {
		        notifyListener();
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

bool
Event::verifyEvent(SDL_Event sdlEvent)
{
    if( (sdlEvent.type == SDL_KEYDOWN) ||
        (sdlEvent.type == SDL_KEYUP) ||
        (sdlEvent.type == SDL_MOUSEBUTTONDOWN) ||
        (sdlEvent.type == SDL_MOUSEBUTTONUP) ||
        (sdlEvent.type == SDL_MOUSEMOTION))
        return true;
    else
        return false;
}
