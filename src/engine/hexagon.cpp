#include "hexagon.h"
#include "log.h"
#include <cmath>
#include "bomba.h"
#include "torre.h"
#include "base.h"
#include "spy.h"
#include "geometry.h"

#include <iostream>

Hexagon::Hexagon(int size, Render * render)
:DrawableObject(render)
{
	this->size = size;
	setSurfaceHeight(size*sin(60*M_PI/180)*2 + 1);
	setSurfaceWidth(size*2 + 1);
	this->object = NULL;
	this->bomba = NULL;
	this->spy = NULL;
	this->vitoria = NULL;
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
	if(sdlEvent.type == SDL_MOUSEMOTION && isMyCoordinate(sdlEvent.motion.x, sdlEvent.motion.y))
		this->setDrawColor(0,0,255, 255);
	else
		this->setDrawColor(0,0,0, 255);	

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
	if(dynamic_cast<Bomba*>(_object))
	{
		if(bomba == NULL)
		{
			bomba =_object;
			return true;
		}
	}	
	else if(dynamic_cast<Torre*>(_object))
	{

		if(object == NULL)
		{
			object = _object;

			if(spy != NULL)
				activateSpy();

			return true;
		}		
	}
	else if(dynamic_cast<Spy*> (_object))
	{
		if(spy == NULL)
		{
			spy = _object;
			activateSpy();
			return true;
		}
	}
	else
	{
		if(vitoria == NULL)
			vitoria = (Image*)_object;

	}
		
	return false;
}

void
Hexagon::activateSpy()
{
	if(object != NULL)
	{
		int numInfo = ((Torre*)object)->spyOnTower(((Spy*)spy)->getLevel());
        ((Spy*)spy)->setNumInformacao(numInfo);
    }
}

void 
Hexagon::draw()
{
    DrawableObject::draw();
    
    for(unsigned int i = 0; i < backgroundImages.size(); i++)
        backgroundImages[i]->draw();
}

void 
Hexagon::update()
{
    for(unsigned int i = 0; i < backgroundImages.size(); i++)
    {
        int x = getX() + (getWidth()/2) - (backgroundImages[i]->getWidth()/2);
		int y = getY() + (getHeight()/2) - (backgroundImages[i]->getHeight()/2);
		
        backgroundImages[i]->setPosition(x, y);
    }

	if(dynamic_cast<Base*> (object))
	{
		int x = getX() - object->getWidth()/4;
		int y = getY() - object->getHeight()/4;
		object->setPosition(x,y);
	}
	else if(object != NULL)
	{
		int x = getX() + (getWidth()/2) - (object->getWidth()/6);
		int y = getY() + (getHeight()/2) - (object->getHeight()/4);	
		object->setPosition(x, y);
	}

	if(spy != NULL)
	{	
		int x = getX() + (getWidth()/2) - (spy->getWidth()/2);
		int y = getY() + (getHeight()/2) - (spy->getHeight()/4);	
		spy->setPosition(x,y);
	}

	if(vitoria != NULL)
		vitoria->setPosition(getX()+2, getY()+2);
}

void 
Hexagon::addBackgroundImage(std::string imagePath)
{
    Image *image = new Image(imagePath, 0, 0);
    backgroundImages.push_back(image);
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

GameObject*
Hexagon::getBomba()
{
	return bomba;
}

GameObject* 
Hexagon::getSpy()
{
	return spy;
}

bool 
Hexagon::haveObject()
{
    if(object == NULL && bomba == NULL)
        return false;
    else
        return true;
}

void 
Hexagon::destroyGameObject()
{
	std::cout<<"destroyGameObject"<<std::endl;
	object = NULL;
	bomba = NULL;
}

bool 
Hexagon::isMyCoordinate(int x, int y)
{	
	int width = 100;
	int height = 87;
	
	if((x > getX()+25) &&
        (x < (getX() + width -25)) &&
        (y > getY()) && 
        (y < (getY() + height)))
	{
		return true;
	}

	if((x > getX()+12) &&
        (x < (getX() + width -12)) &&
        (y > getY() + 22) && 
        (y < (getY() + height-22)))
	{
		return true;
	}

	return false;
}

bool
Hexagon::isVictoryPoint()
{
	return vitoria != NULL;
}
