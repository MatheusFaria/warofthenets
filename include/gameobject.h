#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

class GameObject{
public:
    virtual ~GameObject() {}
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;
	virtual void setPosition(int, int)=0;

	virtual int getX() = 0;
	virtual void setX(int x) = 0;

	virtual int getY() = 0;
	virtual void setY(int y) = 0;

	virtual int getWidth() = 0;
	virtual int getHeight() = 0;

protected:	
	GameObject() {}
	

};



#endif
