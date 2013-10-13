#ifndef MOUSE_EVENT
#define MOUSE_EVENT

#include "event.h"

class MouseEvent : public Event{

public:
    
    class MouseEventListener : public Event::EventListener {
	public:
		virtual ~MouseEventListener(){};
		virtual void onEvent(Event *event, SDL_Event sdlEvent)
		{
		    MouseEvent *mouseEvent = (MouseEvent *) event;
		    onMouseEvent(mouseEvent, sdlEvent);
		}
		virtual void onMouseEvent(MouseEvent *mouseEvent, SDL_Event sdlEvent) = 0;
	};
	

    MouseEvent();
	~MouseEvent();
	
	virtual bool eventInMe(SDL_Event sdlEvent) = 0;
	
	virtual bool verifyEvent(SDL_Event sdlEvent);
	
	static bool isMyEvent(SDL_Event sdlEvent);

};



#endif




































