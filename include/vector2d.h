#ifndef VECTOR_2D_H
#define VECTOR_2D_H

	
class Vector2D{

public:

	Vector2D(int, int);
	Vector2D(){};

	int getX() const;
	int getY() const;

	void setX(int);
	void setY(int);

	Vector2D operator+(const Vector2D& vector) const;


private:

	int x;
	int y;	

};



#endif