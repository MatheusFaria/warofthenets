#ifndef PIXEL_H
#define PIXEL

#include "drawableobject.h"

class Pixel: virtual public DrawableObject{
public:
	Pixel(int = 0, int = 0);
	~Pixel();
	
private:
	void putObjectInSurface();
};

#endif
