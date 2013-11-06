#ifndef SPY_H
#define SPY_H

#include <string>
#include "image.h"

class Spy : public Image{

public:

	Spy(int numLevelSpy = 1, int x=0, int y=0);
	virtual void update();
	virtual void draw();

	int getLevel();

private:

	static std::string path;
	int numLevelSpy;	
};

#endif