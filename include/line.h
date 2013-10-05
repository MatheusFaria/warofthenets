#ifndef LINE_H
#define LINE_H

#include "drawableobject.h"

class Line: virtual public DrawableObject {
public:
	Line(int, int);
	~Line();

private:
	int size;
	int angle;

	void putObjectInSurface();
	int getFinalX();
	int getFinalY();
};

#endif
