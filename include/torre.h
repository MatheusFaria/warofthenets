#ifndef TORRE_H
#define TORRE_H

#include <string>
#include "image.h"

class Torre : public Image{

public:

	Torre(int x=0, int y=0);
	virtual void update();
	virtual void draw();

private:

	static std::string path;	
	int numFrames;
	int actualRow;

};

#endif