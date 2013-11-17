#include "textarea.h"

TextArea::TextArea(std::string textValue, int x, int y)
{
    std::string font = "resources/font/Army.ttf";
    SDL_Color whiteColor = {255, 255, 255, 0};
    
    text = new Text(textValue, 16);
	text->setFont(font);
    text->setColor(whiteColor);
    
    rectangle = new Rectangle(text->getWidth(), 20,Render::getInstance(), true);
    rectangle->setDrawColor(0, 0, 0 , 255);
    
    this->setPosition(x, y);
    
}

void 
TextArea::draw()
{
    rectangle->draw();
    text->draw();
}

void 
TextArea::setText(std::string textValue)
{
    text->setText(textValue);

    delete rectangle;
    
    rectangle = new Rectangle(text->getWidth(), 20,Render::getInstance(), true);
    rectangle->setDrawColor(0, 0, 0 , 255);    
}
    
int
TextArea::getX()
{
    return rectangle->getX();
}

void
TextArea::setX(int x)
{
    rectangle->setX(x);
    
    text->setX(rectangle->getX() + (rectangle->getWidth() - text->getWidth())/2);
}

int
TextArea::getY()
{
    return rectangle->getY();
}

void
TextArea::setY(int y)
{
    rectangle->setY(y);
    
    text->setY(rectangle->getY() + (rectangle->getHeight() - text->getHeight())/2);
}

void
TextArea::setPosition(int x, int y)
{
    this->setX(x);
    this->setY(y);
}




























