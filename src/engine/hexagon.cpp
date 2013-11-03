#include "hexagon.h"
#include "log.h"
#include <cmath>
#include "geometry.h"

#include <iostream>

Hexagon::Hexagon(int size, Render * render)
:DrawableObject(render)
{
	this->size = size;
	setSurfaceHeight(size*sin(60*M_PI/180)*2 + 1);
	setSurfaceWidth(size*2 + 1);
	this->object = NULL;
}

Hexagon::~Hexagon() {}

void 
Hexagon::putObjectInSurface()
{
	int xInitial = this->size, yInitial = this->size*sin(60*M_PI/180);
	for(int i = 0, oldX = 0, oldY = 0; i <= 360; i+=60)
	{
		int newX = Geometry::getLineEndX(i, this->size) + xInitial;
		int newY = Geometry::getLineEndY(i, this->size) + yInitial;
		if(i)
			SDL_RenderDrawLine(getInternalRenderer(), oldX, oldY, newX, newY);
		oldX = newX;
		oldY = newY;
	}

}

bool 
Hexagon::verifyEvent(SDL_Event sdlEvent)
{
	if((sdlEvent.button.state == SDL_RELEASED) &&
            (sdlEvent.type != SDL_MOUSEMOTION))
	{
		return true;
	}

	return false;
}


bool 
Hexagon::eventInMe(SDL_Event sdlEvent)
{
	if(isMyCoordinate(sdlEvent.button.x, sdlEvent.button.y))
	{
		switch(sdlEvent.button.button)
		{
			case SDL_BUTTON_RIGHT:
				setEventMouse(MOUSE_RIGHT);
				break;
			case SDL_BUTTON_LEFT:
				setEventMouse(MOUSE_LEFT);
				break;
			case SDL_BUTTON_MIDDLE:
				setEventMouse(MOUSE_MIDDLE);
				break;
			
		}

		return true;
	}

	return false;
}

bool 
Hexagon::setObject(GameObject* _object)
{
	if(object == NULL)
	{
		object = _object;
		return true;
	}	
	
	return false;
}

void 
Hexagon::update()
{
	if(object != NULL)
		object->setPosition(getX(), getY());
}

void 
Hexagon::setEventMouse(int mouse_state)
{
	resetEventMouse();
	eventMouse[mouse_state] = true;
}

void 
Hexagon::resetEventMouse()
{
	eventMouse[MOUSE_RIGHT] = false;
	eventMouse[MOUSE_LEFT] = false;
	eventMouse[MOUSE_MIDDLE] = false;

}

bool 
Hexagon::isMouseRight()
{
	return eventMouse[MOUSE_RIGHT];
}
bool 
Hexagon::isMouseLeft()
{
	return eventMouse[MOUSE_LEFT];
}
bool 
Hexagon::isMouseMiddle()
{
	return eventMouse[MOUSE_MIDDLE];
}

GameObject* 
Hexagon::getObject()
{
	return object;
}

bool 
Hexagon::haveObject()
{
    if(object == NULL)
        return false;
    else
        return true;
}

void 
Hexagon::destroyGameObject()
{
	object = NULL;
}

bool 
Hexagon::isMyCoordinate(int x, int y)
{
    /*
    std::cout << "\n\n\nisMyCoordinate: " << std::endl;
    
    int centerX = getX() + (getWidth()/2);
	int centerY = getY() + (getHeight()/2);
    
    std::cout << "getX(): " << getX() << std::endl;
	std::cout << "getY(): " << getY() << std::endl;
	std::cout << "getWidth(): " << getWidth() << std::endl;
	std::cout << "getHeight(): " << getHeight() << std::endl;
	std::cout << "centerX: " << centerX << std::endl;
	std::cout << "centerY: " << centerY << std::endl;
	*/
	
	int width = 100;
	int height = 87;
	
	if((x > getX()) &&
        (x < (getX() + width)) &&
        (y > getY()) && 
        (y < (getY() + height)))
	{
		return true;
	}

	return false;
}
