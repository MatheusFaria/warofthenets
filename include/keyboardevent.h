#ifndef KEYBOARDEVENT_H
#define KEYBOARDEVENT_H

#include "event.h"

class KeyboardEvent : public Event{

public:
    
    class KeyboardEventListener : public Event::EventListener {
	public:
		virtual ~KeyboardEventListener(){};
		virtual void onEvent(Event *event)
		{
		    KeyboardEvent *keyboardEvent = (KeyboardEvent *) event;
		    onKeyboardEvent(keyboardEvent);
		}
		virtual void onKeyboardEvent(KeyboardEvent *keyboardEvent) = 0;
	};
	

    KeyboardEvent();
	~KeyboardEvent();
	
	virtual bool eventInMe(SDL_Event sdlEvent) = 0;
	
	virtual bool verifyEvent(SDL_Event sdlEvent);
};

#endif























































