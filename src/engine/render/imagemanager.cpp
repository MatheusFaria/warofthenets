#include "imagemanager.h"

ImageManager::ImageManager() {}
ImageManager::~ImageManager() {}

void
ImageManager::addImage(std::string id, Render * render, int sprites, int spriteslines, int spritescols)
{
	if(!this->imageMap[id])
	{
		this->imageMap[id] = new Image(id, render, sprites, spriteslines, spritescols);
		this->referenceMap[id] = 1;
	}
	else
		this->referenceMap[id]++;
}

Image *
ImageManager::getImage(std::string id)
{
	if(this->referenceMap[id])
		this->referenceMap[id]++;
	return this->imageMap[id];
}

void
ImageManager::releaseImage(std::string id)
{
	if(this->referenceMap[id])
		this->referenceMap[id]--;
}

void
ImageManager::removeImage(std::string id)
{
	if(this->imageMap[id])
	{
		this->referenceMap[id]--;
		if(this->referenceMap[id] <= 0)
		{
			delete this->imageMap[id];
			this->imageMap.erase(id);
			referenceMap.erase(id);
		}
	}
}

