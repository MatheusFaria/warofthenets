#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <map>
#include <vector>
#include <string>
#include "texture.h"

class TextureManager{

public:
	TextureManager();
	~TextureManager();

	void addTexture(std::string, Texture *);
	void removeTexture(std::string);
	Texture * getTexture(std::string);

	void renderAll() const;
	void renderRange(int, int) const;
	void renderTexture(std::string);
	
	void setPriority(std::string, int);

	int getMaxPriority() const;
private:
	std::map<std::string, Texture *> textureMap;
	std::vector<Texture *> priorityOrder;
	
 	void eraseTextureFromPriorityOrder(std::string);
};


#endif
