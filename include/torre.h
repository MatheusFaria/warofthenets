#ifndef TORRE_H
#define TORRE_H

#include <string>
#include "image.h"

class Torre : public Image{

public:

	Torre(int tipoTorre, int numLevelTower = 1, int x=0, int y=0, std::string path = "resources/img/tower.png");
	
	virtual void update();
	virtual void draw();
	virtual void clean();
	
	virtual void setPosition(int, int);
	
	static int getCustoAtualizacao();
	static void setCustoAtualizacao(int _custoAtualizacao);
	static int getCustoUnidade();
	static void setCustoUnidade(int _custoUnidade);
	
	int getNumLevel();
	void setNumLevel(int numLevel);

	void incActualColumn();
	virtual int getInformacao();
	int spyOnTower(int levelSpy);
	
	void removeSpy();

	bool playSound();

	bool isAliada();

	static int ALIADA ;
	static int INIMIGA ;

protected:

	int numFrames;
	int numLevels;

private:

	int actualRow;
	int numInformacao;
	int numLevelTower;
	std::string constructSound;
	
	static int custoAtualizacao;
	static int custoUnidade;

	int tipoTorre;
	
	Image *imageAliada;

	

};

#endif
