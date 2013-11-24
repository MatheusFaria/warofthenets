#ifndef PARSE_ARQUIVO_H
#define PARSE_ARQUIVO_H

#include "vector2d.h"
#include <map>
#include <string>

class ParseArquivo{

public:

	ParseArquivo();

	bool loadArquivo(std::string path);

	char getTipObjetivo() const;
	Vector2D getBaseAlidaPosicao() const;
	Vector2D getBaseInimigaPosicao() const;
	Vector2D getPontoVitoriaAliado() const;
	Vector2D getPontoVitoriaInimigo() const;
	int getNumeroRecursoInicial() const;

	int getCustoTorre() const;
	int getCustoBomba() const;
	int getCustoEspiao() const;

	int getEvolucaoCustoTorre() const;
	int getEvolucaoCustoEspiao() const;
	int getEvolucaoCustoBomba() const;

	int getUpgradeTorre() const;
	int getUpgradeBomba() const;	
	int getUpgradeEspiao() const;

	char getTipoFundo() const;

	char getTipoBaseAliada() const;
	char getTipoBaseInimiga() const;



private:	

	map<std::string, std::string> dados;

	char tipoObjetivo;
	Vector2D baseAlidaPosicao;
	Vector2D baseInimigaPosicao;
	Vector2D pontoVitoriaAliado;
	Vector2D pontoVitoriaInimigo;

	int numeroRecursoInicial;
	int custoTorre;
	int custoBomba;
	int custoEspiao;

	int evolucaoCustoTorre;
	int evolucaoCustoEspiao;
	int evolucaoCustoBomba;

	int upgradeTorre;
	int upgradeBomba;	
	int upgradeEspiao;

	char tipoFundo;

	char tipoBaseAliada;
	char tipoBaseInimiga;
};

#endif