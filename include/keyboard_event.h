#ifndef KEYBOARD_EVENT_H
#define KEYBOARD_EVENT_H

#include "event.h"

class KeyboardEvent : public Event{

public:
    
    class KeyboardEventListener : public Event::EventListener {
	public:
		virtual ~KeyboardEventListener(){};
		virtual void onEvent(Event *event, SDL_Event sdlEvent)
		{
		    KeyboardEvent *keyboardEvent = (KeyboardEvent *) event;
		    onKeyboardEvent(keyboardEvent, sdlEvent);
		}
		virtual void onKeyboardEvent(KeyboardEvent *keyboardEvent, SDL_Event sdlEvent) = 0;
	};
	

    KeyboardEvent();
	~KeyboardEvent();
	
	virtual bool eventInMe(SDL_Event sdlEvent) = 0;
	
	virtual bool verifyEvent(SDL_Event sdlEvent);
};

#endif























































