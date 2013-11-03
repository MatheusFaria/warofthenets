#ifndef MOUSEMOTION
#define MOUSEMOTION

#include "mouseevent.h"

class MouseMotion : public MouseEvent {

public:

    class MouseMotionListener : public MouseEvent::MouseEventListener {
	public:
		virtual ~MouseMotionListener(){};
		virtual void onMouseEvent(MouseEvent *mouseEvent)
		{
		    MouseMotion *mouseMotion = (MouseMotion *) mouseEvent;
		    onMouseMotion(mouseMotion);
		}
		virtual void onMouseMotion(MouseMotion *mouseMotion) = 0;
	};
	

    MouseMotion();
	~MouseMotion();
	
	virtual bool eventInMe(SDL_Event sdlEvent) = 0;
	
	virtual bool verifyEvent(SDL_Event sdlEvent);
};




#endif
















































