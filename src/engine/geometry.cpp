#include "geometry.h"
#include <cmath>

int
Geometry::getLineEndX(int a, int r)
{
	return r*sin((90 - a)*M_PI/180);
}

int
Geometry::getLineEndY(int a, int r)
{
	return r*sin(a*M_PI/180);
}
