#ifndef MOUSE_CLICK
#define MOUSE_CLICK

#include "mouse_event.h"

class MouseClick : public MouseEvent {

public:

    class MouseClickListener : public MouseEvent::MouseEventListener {
	public:
		virtual ~MouseClickListener(){};
		virtual void onMouseEvent(MouseEvent *mouseEvent, SDL_Event sdlEvent)
		{
		    MouseClick *mouseClick = (MouseClick *) mouseEvent;
		    onMouseClick(mouseClick, sdlEvent);
		}
		virtual void onMouseClick(MouseClick *mouseClick, SDL_Event sdlEvent) = 0;
	};
	

    MouseClick();
	~MouseClick();
	
	virtual bool eventInMe(SDL_Event sdlEvent) = 0;
	
	virtual bool verifyEvent(SDL_Event sdlEvent);
};




#endif










































