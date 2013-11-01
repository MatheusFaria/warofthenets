#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "drawableobject.h"

class Rectangle: virtual public DrawableObject {
public:
	Rectangle(int, int, Render *, bool=false); 
	~Rectangle();

private:
	SDL_Rect rect;
	bool filled;

	void putObjectInSurface();
};

#endif
