#ifndef MOUSE_MOTION
#define MOUSE_MOTION

#include "mouse_event.h"

class MouseMotion : public MouseEvent {

public:

    class MouseMotionListener : public MouseEvent::MouseEventListener {
	public:
		virtual ~MouseMotionListener(){};
		virtual void onMouseEvent(MouseEvent *mouseEvent, SDL_Event sdlEvent)
		{
		    MouseMotion *mouseMotion = (MouseMotion *) mouseEvent;
		    onMouseMotion(mouseMotion, sdlEvent);
		}
		virtual void onMouseMotion(MouseMotion *mouseMotion, SDL_Event sdlEvent) = 0;
	};
	

    MouseMotion();
	~MouseMotion();
	
	virtual bool eventInMe(SDL_Event sdlEvent) = 0;
	
	virtual bool verifyEvent(SDL_Event sdlEvent);
};




#endif
















































