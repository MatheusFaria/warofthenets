#ifndef HEXAGON_H
#define HEXAGON_H

#include "drawableobject.h"

class Hexagon: virtual public DrawableObject{
public:
	Hexagon(int);
	~Hexagon();
	
private:
	int sideSize;

	void putObjectInSurface();
};

#endif
