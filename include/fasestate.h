#ifndef FASESTATE_H
#define FASESTATE_H

#include "gameestate.h"
#include "gameobject.h"
#include "mouseclick.h"
#include "menubutton.h"
#include "image.h"
#include <vector>


class FaseState : public GameState, MouseClick::MouseClickListener{

public:

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();
	
	virtual void enable();
	virtual void disable();

	virtual std::string getStateId() const;
	
	virtual void onMouseClick(MouseClick *mouseClick);

private:

    void receberMensagens();
    void iniciarFase(string nomeFase);
    void enviarIniciarFase(string nomeFase);

	static const std::string faseId;
	std::vector<MenuButton*> vectorButtons;
	
	Image *imgTitulo;
	MenuButton *btnBrasil;
	MenuButton *btnAlemanha;
	MenuButton *btnJapao;
	MenuButton *btnIndia;
	MenuButton *btnRussia;
	
	void setEnableButtons(bool enable);
	
	float velocity;
	float previousTime;

	SDL_Renderer *rend;
    SDL_Rect rectBackground;
    int alpha;

};


#endif
