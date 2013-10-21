#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include "image.h"
#include <map>
#include <string>

class ImageManager{
public:
	ImageManager();
	~ImageManager();

	void addImage(std::string, Render *, int = 1, int = 1, int = 1);
	Image * getImage(std::string);
	void releaseImage(std::string);
	void removeImage(std::string);

private:
	std::map<std::string, Image *> imageMap;
	std::map<std::string, int> referenceMap;
};

#endif
