#include "hexagon.h"
#include "log.h"

Hexagon::Hexagon(int size)
:DrawableObject(MIN_WIDTH, MIN_HEIGHT)
{
	this->sideSize = size;
}

Hexagon::~Hexagon() {}

void 
Hexagon::putObjectInSurface()
{

}
