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
LoaderParams::getX()
{
	return x;
}

int 
LoaderParams::getY()
{
	return y;
}

int 
LoaderParams::getWidth()
{
	return width;
}

int 
LoaderParams::getHeight()
{
	return height;
}

string 
LoaderParams::getImageId()
{
	return imageId;
}

