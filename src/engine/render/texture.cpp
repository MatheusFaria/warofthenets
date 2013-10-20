#include "texture.h"
#include "log.h"

Texture::Texture(RenderableObject * obj, int x, int y, bool animation)
{
	this->object = obj;
	this->currentSprite = 0;
	this->x = x;
	this->y = y;
	this->automaticAnimation = animation;
	this->spriteSkip = 1;
}

Texture::~Texture() {}

RenderableObject * 
Texture::getObject() const
{
	return this->object;
}

int 
Texture::getX() const
{
	return this->x;
}

int Texture::getY() const
{
	return this->y;
}

void 
Texture::setSprite(int frame)
{
	this->currentSprite = frame;
}

void 
Texture::setX(int x)
{
	this->x = x;
}

void 
Texture::setY(int y)
{
	this->y = y;
}

void 
Texture::setPostion(int x, int y)
{
	setX(x);
	setY(y);
}

void
Texture::incSprite()
{
	this->currentSprite+= this->spriteSkip;
	this->currentSprite %= this->object->getNumberSprites();
}

void
Texture::decSprite()
{
	this->currentSprite-= this->spriteSkip;
	if(this->currentSprite < 0)
		this->currentSprite = this->object->getNumberSprites() - 1;
}

void
Texture::render()
{
	SDL_Texture * texture = this->object->getTexture();
	int spriteW, spriteH;

	if(this->automaticAnimation)
		this->incSprite();

	spriteW = this->object->getWidth() / this->object->getSpritesColumns();
	spriteH = this->object->getHeight() / this->object->getSpritesLines();

	SDL_Rect dst, clip;
	
	dst.x = this->x;
	dst.y = this->y;

	clip.w = dst.w = spriteW;
	clip.h = dst.h = spriteH;

	int col =  this->currentSprite % this->object->getSpritesColumns();
	int line = this->currentSprite / this->object->getSpritesColumns(); 

	clip.x = col*spriteW;
	clip.y = line*spriteH;

	SDL_RenderCopy(this->object->getRenderer(), texture, &clip, &dst);
}

void Texture::enableAutomaticAnimation(int spriteSkip)
{
	this->automaticAnimation = true;
	this->spriteSkip = spriteSkip;
}

void Texture::disableAutomaticAnimation()
{
	this->automaticAnimation = false;
	this->spriteSkip = 1;
}
