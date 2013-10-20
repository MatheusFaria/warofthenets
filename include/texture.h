#ifndef TEXTURE_H
#define TEXTURE_H

#include "renderableobject.h"
#include <string>

class Texture{
public:
	Texture(RenderableObject *, int, int, bool = false);
	~Texture();

	RenderableObject * getObject() const;

	int getX() const;
	int getY() const;

	void setSprite(int);
	void setX(int);
	void setY(int);
	void setPostion(int, int);

	void incSprite();
	void decSprite();

	void render();
	void enableAutomaticAnimation(int = 1);
	void disableAutomaticAnimation();

private:
	RenderableObject * object;
	int currentSprite;
	int x, y;
	bool automaticAnimation;
	int spriteSkip;
};

#endif
