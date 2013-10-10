#include "vector2d.h"

Vector2D::Vector2D(int _x=0, int _y=0)
{
	x=_x;
	y=_y;
}

void
Vector2D::setX(int _x)
{
	x = _x;
}

void
Vector2D::setY(int _y)
{
	y =_y;
}

int
Vector2D::getX() const
{
	return x;
}

int
Vector2D::getY() const
{
	return y;
}

Vector2D
Vector2D::operator+(const Vector2D& vector) const
{
	return Vector2D(x + vector.x, y + vector.y);
}