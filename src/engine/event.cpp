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
    return Event::isMyEvent(sdlEvent);
}

bool
Event::isMyEvent(SDL_Event sdlEvent)
{
    return true;
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






































