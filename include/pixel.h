#ifndef PIXEL_H
#define PIXEL

#include "drawableobject.h"

class Pixel: virtual public DrawableObject{
public:
	Pixel(Render * render);
	~Pixel();
	
private:
	void putObjectInSurface();
};

#endif
