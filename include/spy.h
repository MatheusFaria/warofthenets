#ifndef SPY_H
#define SPY_H

#include <string>
#include "image.h"

class Spy : public Image{

public:

	Spy(int numLevelSpy = 1, int x=0, int y=0);
	virtual void update();
	virtual void draw();
    
	static int getCustoAtualizacao();
	static void setCustoAtualizacao(int _custoAtualizacao);
	static int getCustoUnidade();
	static void setCustoUnidade(int _custoUnidade);

	int getLevel();

    int getInformacao() const;
    void setNumInformacao(int numInfo);
    
private:

	void playSound();

	static std::string path;
	int numLevelSpy;	
	int numInformacao;
	static int custoAtualizacao;
	static int custoUnidade;
};

#endif
