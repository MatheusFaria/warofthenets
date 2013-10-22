#ifndef HEXAGON_H
#define HEXAGON_H

#include "drawableobject.h"

class Hexagon: virtual public DrawableObject{
public:
	Hexagon(int, Render *);
	~Hexagon();
	
private:
	int size;

	void putObjectInSurface();
};

#endif
