#include "texturemanager.h"
#include <algorithm>
#include <log.h>

TextureManager::TextureManager() {}

TextureManager::~TextureManager() {}

void
TextureManager::addTexture(std::string label, Texture * tex)
{
	if(!this->textureMap[label])
	{
		this->textureMap[label] = tex;
		this->priorityOrder.push_back(tex);
	}
}

void
TextureManager::removeTexture(std::string label)
{
	if(this->textureMap[label])
	{
		this->eraseTextureFromPriorityOrder(label);
		this->textureMap.erase(label);
	}
}

void 
TextureManager::eraseTextureFromPriorityOrder(std::string label)
{
	Texture * texToRemove = this->textureMap[label];
	for(std::vector<Texture *>::iterator tex = this->priorityOrder.begin(); tex != this->priorityOrder.end(); tex++)
	{
		if(*tex == texToRemove)
		{
			this->priorityOrder.erase(tex);
			break;
		}
	}
}

Texture *
TextureManager::getTexture(std::string label)
{
	return this->textureMap[label];
}

void
TextureManager::renderAll() const
{
	renderRange(0, (int) this->priorityOrder.size() - 1);
}

void
TextureManager::renderRange(int a, int b) const
{
	if(a > b)
		std::swap(a, b);
	if(a >= 0 && b < (int) this->priorityOrder.size())
	{
		for(int priorityToRender = a; priorityToRender <= b; priorityToRender++)
			this->priorityOrder[priorityToRender]->render();
	}
}

void
TextureManager::renderTexture(std::string label)
{
	this->textureMap[label]->render();
}

void
TextureManager::setPriority(std::string label, int priority)
{
	
}

int
TextureManager::getMaxPriority() const
{
	return (int) this->priorityOrder.size();
}
