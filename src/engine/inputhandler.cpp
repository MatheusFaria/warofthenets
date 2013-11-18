#include "inputhandler.h"

using namespace std;

InputHandler *InputHandler::instance = NULL;

InputHandler::InputHandler()
{
    initLists();
    active = true;
}

InputHandler::~InputHandler()
{
    deleteLists();
}

InputHandler *
InputHandler::getInstance()
{
    if(instance == NULL)
        instance = new InputHandler();
    
    return instance;
}

void
InputHandler::sendSdlEvent(SDL_Event sdlEvent)
{
    if(!active)
        return;
    
    sendSdlEventToListEvent(sdlEvent);
    sendSdlEventToListKeyboardEvent(sdlEvent);
    sendSdlEventToListMouseEvent(sdlEvent);
    sendSdlEventToListMouseClick(sdlEvent);
    sendSdlEventToListMouseMotion(sdlEvent);
    
}

void
InputHandler::sendSdlEventToListEvent(SDL_Event sdlEvent)
{
    list<Event *>::iterator it;
    
    for(it = listEvent->begin(); it != listEvent->end(); it++)
    {
        if((*it)->sendMeToListener(sdlEvent))
            break;
    }
}

void
InputHandler::sendSdlEventToListKeyboardEvent(SDL_Event sdlEvent)
{
    list<KeyboardEvent *>::iterator it;
    
    for(it = listKeyboardEvent->begin(); it != listKeyboardEvent->end(); it++)
    {
        if((*it)->sendMeToListener(sdlEvent))
            break;
    }
}

void
InputHandler::sendSdlEventToListMouseEvent(SDL_Event sdlEvent)
{
    list<MouseEvent *>::iterator it;
    
    for(it = listMouseEvent->begin(); it != listMouseEvent->end(); it++)
    {
        if((*it)->sendMeToListener(sdlEvent))
            break;
    }
}

void
InputHandler::sendSdlEventToListMouseClick(SDL_Event sdlEvent)
{
    list<MouseClick *>::iterator it;
    
    for(it = listMouseClick->begin(); it != listMouseClick->end(); it++)
    {
        if((*it)->sendMeToListener(sdlEvent))
        {
            if( (*it)->isFocusable() )
            {
                cleanFocused();
                (*it)->setFocused(true);
                (*it)->onFocusChange();
            }
            
            break;
        }
    }
}

void
InputHandler::sendSdlEventToListMouseMotion(SDL_Event sdlEvent)
{
    list<MouseMotion *>::iterator it;
    
    for(it = listMouseMotion->begin(); it != listMouseMotion->end(); it++)
    {
        if((*it)->sendMeToListener(sdlEvent))
            break;
    }
}

void 
InputHandler::cleanFocused()
{
    list<Event *>::iterator itEvent;
    list<KeyboardEvent *>::iterator itKeyboardEvent;
    list<MouseEvent *>::iterator itMouseEvent;
    list<MouseClick *>::iterator itMouseClick;
    list<MouseMotion *>::iterator itMouseMotion;
    
    for(itEvent = listEvent->begin(); itEvent != listEvent->end(); itEvent++)
    {
        (*itEvent)->setFocused(false);
        (*itEvent)->onFocusChange();        
    }
    
    for(itKeyboardEvent = listKeyboardEvent->begin(); itKeyboardEvent != listKeyboardEvent->end(); itKeyboardEvent++)
    {
        (*itKeyboardEvent)->setFocused(false);
        (*itKeyboardEvent)->onFocusChange();        
    }
        
    for(itMouseEvent = listMouseEvent->begin(); itMouseEvent != listMouseEvent->end(); itMouseEvent++)
    {
        (*itMouseEvent)->setFocused(false);
        (*itMouseEvent)->onFocusChange();        
    }
        
    for(itMouseClick = listMouseClick->begin(); itMouseClick != listMouseClick->end(); itMouseClick++)
    {
        (*itMouseClick)->setFocused(false);
        (*itMouseClick)->onFocusChange();        
    }
        
    for(itMouseMotion = listMouseMotion->begin(); itMouseMotion != listMouseMotion->end(); itMouseMotion++)
    {
        (*itMouseMotion)->setFocused(false);
        (*itMouseMotion)->onFocusChange();        
    }
    
    
}

void
InputHandler::initLists()
{
    listEvent = new list<Event *>();
    listKeyboardEvent = new list<KeyboardEvent *>;
    listMouseEvent = new list<MouseEvent *>;
    listMouseClick = new list<MouseClick *>;
    listMouseMotion = new list<MouseMotion *>;
}

void
InputHandler::deleteLists()
{
    delete listEvent;
    delete listKeyboardEvent;
    delete listMouseEvent;
    delete listMouseClick;
    delete listMouseMotion;
}

void
InputHandler::reset()
{
    deleteLists();
    initLists();
}

bool
InputHandler::isActive()
{
    return active;
}

void
InputHandler::setActive(bool active)
{
    this->active = active;
}

void
InputHandler::addEvent(Event *event)
{
    listEvent->push_front(event);
}

void
InputHandler::addKeyboardEvent(KeyboardEvent *keyboardEvent)
{
    listKeyboardEvent->push_front(keyboardEvent);
}

void
InputHandler::addMouseEvent(MouseEvent *mouseEvent)
{
    listMouseEvent->push_front(mouseEvent);
}

void
InputHandler::addMouseClick(MouseClick *mouseClick)
{
    listMouseClick->push_front(mouseClick);
}

void
InputHandler::addMouseMotion(MouseMotion *mouseMotion)
{
    listMouseMotion->push_front(mouseMotion);
}

void
InputHandler::removeEvent(Event *event)
{
    listEvent->remove(event);
}

void
InputHandler::removeKeyboardEvent(KeyboardEvent *keyboardEvent)
{
    listKeyboardEvent->remove(keyboardEvent);
}

void
InputHandler::removeMouseEvent(MouseEvent *mouseEvent)
{
    listMouseEvent->remove(mouseEvent);
}

void
InputHandler::removeMouseClick(MouseClick *mouseClick)
{
    listMouseClick->remove(mouseClick);
}

void
InputHandler::removeMouseMotion(MouseMotion *mouseMotion)
{
    listMouseMotion->remove(mouseMotion);
}
















