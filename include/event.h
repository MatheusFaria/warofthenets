#ifndef EVENT_H
#define EVENT_H

#include "SDL2/SDL.h"

class Event {

public:
	
	class EventListener {
	public:
		virtual ~EventListener(){};
		virtual void onEvent(Event *event) = 0;
	};
		
		
	Event();
	~Event();
		
	virtual bool eventInMe(SDL_Event sdlEvent) = 0;
	
	virtual bool verifyEvent(SDL_Event sdlEvent);
	
	virtual void onFocusChange();
			
	void notifyListener();
	
	bool sendMeToListener(SDL_Event event);
	
	bool isActive();
	void setActive(bool active);
	
	bool isFocusable();
	void setFocusable(bool focusable);
	
	bool isFocused();
	void setFocused(bool focused);	
	
	EventListener * getEventListener();
	void setEventListener(EventListener *eventListener);

private:
	EventListener *eventListener;
	
	bool active;
	
	bool focusable;
	bool focused;
};


#endif
