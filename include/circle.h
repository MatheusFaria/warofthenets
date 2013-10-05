#ifndef CIRCLE_H
#define CIRCLE_H

#include "drawableobject.h"

class Circle: virtual public DrawableObject{
public:
	Circle(int, bool=false);
	~Circle();

private:
	int radius;
	bool filled;

	void putObjectInSurface();
	int getFinalX(int, int);
	int getFinalY(int, int);
};

#endif
