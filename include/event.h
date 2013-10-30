#ifndef EVENT_H
#define EVENT_H

#include "SDL2/SDL.h"

class Event {

public:
	
	class EventListener {
	public:
		virtual ~EventListener(){};
		virtual void onEvent(Event *event, SDL_Event sdlEvent) = 0;
	};
		
		
	Event();
	~Event();
		
	virtual bool eventInMe(SDL_Event sdlEvent) = 0;
	
	virtual bool verifyEvent(SDL_Event sdlEvent);
	
	static bool isMyEvent(SDL_Event sdlEvent);
		
	void notifyListener(SDL_Event sdlEvent);
	
	bool sendMeToListener(SDL_Event event);
	
	
	bool isActive();
	void setActive(bool active);
	
	
	EventListener * getEventListener();
	void setEventListener(EventListener *eventListener);

private:
	EventListener *eventListener;
	
	bool active;
};


#endif