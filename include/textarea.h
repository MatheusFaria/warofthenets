#ifndef TEXTAREA_H
#define TEXTAREA_H

#include "rectangle.h"
#include "text.h"

class TextArea {

public:
    TextArea(std::string text = " ", int x = 0, int y = 0);
    
    void setText(std::string textValue);
    
    //void update();
    void draw();
        
    int getX();
    void setX(int x);
    
    int getY();
    void setY(int y);
    
    void setPosition(int x, int y);

private:
    Rectangle *rectangle;
    Text *text;
};



#endif

