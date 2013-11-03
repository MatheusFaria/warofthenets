#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

class GameObject{
public:
    virtual ~GameObject() {}
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;
	virtual void setPosition(int, int)=0;

protected:	
	GameObject() {}
	

};



#endif
