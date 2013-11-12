#ifndef TORRE_H
#define TORRE_H

#include <string>
#include "image.h"

class Torre : public Image{

public:

	Torre(int numLevelTower = 1, int x=0, int y=0);
	virtual void update();
	virtual void draw();
	
	static int getCustoAtualizacao();
	static void setCustoAtualizacao(int _custoAtualizacao);

	void incActualColumn();
	int getInformacao();
	int spyOnTower(int levelSpy);

	bool playSound();

private:

	static std::string path;	
	int numFrames;
	int actualRow;
	int numInformacao;
	int numLevelTower;
	std::string constructSound;
	static int custoAtualizacao;

};

#endif
