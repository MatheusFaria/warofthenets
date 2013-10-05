#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "drawableobject.h"

class Rectangle: virtual public DrawableObject {
public:
	Rectangle(int, int, int=0, int=0, bool=false); 
	~Rectangle();

	void fill();

private:
	SDL_Rect rect;
	bool filled;

	void putObjectInSurface();
};

#endif
