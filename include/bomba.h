#ifndef BOMBA_H
#define BOMBA_H

#include "image.h"
#include "hexagon.h"
#include <map>
#include <vector>
#include <string>
#include <queue>

class Bomba : public Image{

public:

	Bomba(int raioDestruicao = 1, int x=0, int y=0);
	virtual void update();
	virtual void draw();
    
	static int getCustoAtualizacao();
	static void setCustoAtualizacao(int _custoAtualizacao);

	void explode(map<Hexagon*, vector<Hexagon*>> grafoHexagon, Hexagon *hex);
	std::vector<Hexagon *> getVetorDestruicao();

	bool isAnimating();

	bool playExploiveSound();

private:

	int tempInicial;
	bool inAnimate;

	static std::string path;	
	int numFrames;
	int actualRow;
	int raioDestruicao;
	static int custoAtualizacao;


	std::map<Hexagon *, bool> mapaVisitado;
	std::queue<Hexagon *> filaVisitar;
	std::vector<Hexagon *> vetorDestruicao;

	std::string explosionSound;

	void explodeRecursivo(map<Hexagon*, vector<Hexagon*>> grafoHexagon, int num);
	void animate();
};

#endif
