#ifndef LOADER_PARAMS_H
#define LOADER_PARAMS_H

#include <string>

using namespace std;

class LoaderParams{

public:

	LoaderParams(int _x, int _y, int _width, int _height, string _imageId);

	int getX() const;
	int getY() const;
	int getWidth() const;
	int getHeight() const;
	string getImageId() const;

private:

	int	x;
	int y;
	int width;
	int height;
	string imageId;
};

#endif