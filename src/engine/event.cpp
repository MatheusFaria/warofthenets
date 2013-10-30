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






































