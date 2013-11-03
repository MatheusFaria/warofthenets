#ifndef CIRCLE_H
#define CIRCLE_H

#include "drawableobject.h"

class Circle: virtual public DrawableObject{
public:
	Circle(int, Render *);
	~Circle();

private:
	int radius;

	void putObjectInSurface();
};

#endif
