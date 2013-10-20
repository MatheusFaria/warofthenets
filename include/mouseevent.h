#ifndef MOUSEEVENT
#define MOUSEEVENT

#include "event.h"

class MouseEvent : public Event{

public:
    
    class MouseEventListener : public Event::EventListener {
	public:
		virtual ~MouseEventListener(){};
		virtual void onEvent(Event *event)
		{
		    MouseEvent *mouseEvent = (MouseEvent *) event;
		    onMouseEvent(mouseEvent);
		}
		virtual void onMouseEvent(MouseEvent *mouseEvent) = 0;
	};
	

    MouseEvent();
	~MouseEvent();
	
	virtual bool eventInMe(SDL_Event sdlEvent) = 0;
	
	virtual bool verifyEvent(SDL_Event sdlEvent);
	
	static bool isMyEvent(SDL_Event sdlEvent);

};



#endif




































