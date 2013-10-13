#ifndef INPUT_HANDLER
#define INPUT_HANDLER

#include <list>
#include "event.h"
#include "keyboard_event.h"
#include "mouse_event.h"
#include "mouse_click.h"
#include "mouse_motion.h"

using namespace std;

class InputHandler {

public:
    static InputHandler * getInstance();
    ~InputHandler();
    
    void sendSdlEvent(SDL_Event sdlEvent);
    
    void reset();
    
    void addEvent(Event *event);
    void addKeyboardEvent(KeyboardEvent *keyboardEvent);
    void addMouseEvent(MouseEvent *mouseEvent);
    void addMouseClick(MouseClick *mouseClick);
    void addMouseMotion(MouseMotion *mouseMotion);
    
    void removeEvent(Event *event);
    void removeKeyboardEvent(KeyboardEvent *keyboardEvent);
    void removeMouseEvent(MouseEvent *mouseEvent);
    void removeMouseClick(MouseClick *mouseClick);
    void removeMouseMotion(MouseMotion *mouseMotion);
    
    bool isActive();
    void setActive(bool active);
    
private:
    InputHandler();
    static InputHandler *instance;
    
    void initLists();
    void deleteLists();
    
    void sendSdlEventToListEvent(SDL_Event sdlEvent);
    void sendSdlEventToListKeyboardEvent(SDL_Event sdlEvent);
    void sendSdlEventToListMouseEvent(SDL_Event sdlEvent);
    void sendSdlEventToListMouseClick(SDL_Event sdlEvent);
    void sendSdlEventToListMouseMotion(SDL_Event sdlEvent);
    
    list<Event *> *listEvent;
    list<KeyboardEvent *> *listKeyboardEvent;
    list<MouseEvent *> *listMouseEvent;
    list<MouseClick *> *listMouseClick;
    list<MouseMotion *> *listMouseMotion;
    
    bool active;
        
};


#endif














