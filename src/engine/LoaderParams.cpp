#include "LoaderParams.h"

LoaderParams::LoaderParams(int _x, int _y, int _width, int _height, string _imageId)
{
	x = _x;
	y = _y;
	width = _width;
	height=_height;
	imageId = _imageId;
}

int 
LoaderParams::getX() const
{
	return x;
}

int 
LoaderParams::getY() const
{
	return y;
}

int 
LoaderParams::getWidth() const
{
	return width;
}

int 
LoaderParams::getHeight() const
{
	return height;
}

string 
LoaderParams::getImageId() const
{
	return imageId;
}

