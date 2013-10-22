#ifndef LINE_H
#define LINE_H

#include "drawableobject.h"

class Line: virtual public DrawableObject {
public:
	Line(int, int, Render *);
	~Line();

private:
	int size;
	int angle;

	void putObjectInSurface();
};

#endif
