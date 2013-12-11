#include "parseArquivo.h"
#include "vector2d.h"
#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>

bool
ParseArquivo::loadArquivo(std::string path)
{
	unsigned int i=0;
	char buffer[4096];
	std::string data[] = {"objetivos", "posBaseAliada", "posBaseInimiga", "ptVitAliada", "ptVitoriaInimiga", 
							"recursoInicial", "custoTorre", "custoBomba", "custoEspiao", "evolTorre", "evolBomba",
							"evolEspiao", "upTorre", "upBomba", "upEspiao", "tipoFundo", "tipoBaseAliada",
							"tipoBaseInimiga", "descricaoObjetivo", "numInfoVitoria"};
	std::string param;
		
	std::ifstream arquivo(path.c_str());

	
	void (ParseArquivo::*funcao[])() = {&ParseArquivo::setTipoObjetivo, &ParseArquivo::setBaseAlidaPosicao,
				 			&ParseArquivo::setBaseInimigaPosicao, &ParseArquivo::setPontoVitoriaAliado,
							&ParseArquivo::setPontoVitoriaInimigo, &ParseArquivo::setNumeroRecursoInicial, 
							&ParseArquivo::setCustoTorre, &ParseArquivo::setCustoBomba, &ParseArquivo::setCustoEspiao,
 							&ParseArquivo::setEvolucaoCustoTorre, &ParseArquivo::setEvolucaoCustoEspiao,
							&ParseArquivo::setEvolucaoCustoBomba, &ParseArquivo::setUpgradeTorre,
							&ParseArquivo::setUpgradeBomba, &ParseArquivo::setUpgradeEspiao,
							&ParseArquivo::setTipoFundo, &ParseArquivo::setTipoBaseAliada,
							&ParseArquivo::setTipoBaseInimiga, &ParseArquivo::setDescricaoObjetivo,
							&ParseArquivo::setNumInfoVitoria};
	

	//void (ParseArquivo::*funcao)() = &ParseArquivo::setTipoObjetivo;

	while(arquivo.getline(buffer, 4096)){
		param = buffer;
		dados[data[i++]] = param;
	}

	arquivo.close();

	for(int i = 0; i < 20; i++)
		(this->*funcao[i])();

	return true;
}

void 
ParseArquivo::setTipoObjetivo()
{
	const char* objetivo = (const char*)dados["objetivos"].c_str();
	sscanf(objetivo,"%c", &tipoObjetivo);
}

void
ParseArquivo:: setBaseAlidaPosicao()
{
	int x, y; 
	const char* posBaseAliada = (const char*)dados["posBaseAliada"].c_str();
	sscanf(posBaseAliada,"%d %d", &x, &y);

	baseAlidaPosicao = Vector2D(x,y);
}

void 
ParseArquivo::setBaseInimigaPosicao()
{
	int x, y; 
	const char* posBaseInimiga = (const char*)dados["posBaseInimiga"].c_str();
	sscanf(posBaseInimiga,"%d %d", &x, &y);

	baseInimigaPosicao = Vector2D(x,y);
}

void
ParseArquivo::setPontoVitoriaAliado()
{
	int x, y; 
	const char* ptVitAliada = (const char*)dados["ptVitAliada"].c_str();
	sscanf(ptVitAliada,"%d %d", &x, &y);

	pontoVitoriaAliado = Vector2D(x,y);
}

void
ParseArquivo::setPontoVitoriaInimigo()
{
	int x, y; 
	const char* ptVitInimiga = (const char*)dados["ptVitoriaInimiga"].c_str();
	sscanf(ptVitInimiga,"%d %d", &x, &y);

	pontoVitoriaInimigo = Vector2D(x,y);
}

void 
ParseArquivo::setNumeroRecursoInicial()
{
	this->numeroRecursoInicial = atoi(dados["recursoInicial"].c_str());
}

void 
ParseArquivo::setCustoTorre()
{
	this->custoTorre = atoi(dados["custoTorre"].c_str());
}

void 
ParseArquivo::setCustoBomba()
{
	this->custoBomba = atoi(dados["custoBomba"].c_str());
}

void 
ParseArquivo::setCustoEspiao()
{
	this->custoEspiao = atoi(dados["custoEspiao"].c_str());
}

void 
ParseArquivo::setEvolucaoCustoTorre()
{
	this->evolucaoCustoTorre = atoi(dados["evolTorre"].c_str());
}

void 
ParseArquivo::setEvolucaoCustoEspiao()
{
	this->evolucaoCustoEspiao = atoi(dados["evolEspiao"].c_str());
}

void 
ParseArquivo::setEvolucaoCustoBomba()
{
	this->evolucaoCustoBomba = atoi(dados["evolBomba"].c_str());
}


void 
ParseArquivo::setUpgradeTorre()
{
	this->upgradeTorre = atoi(dados["upTorre"].c_str());
}

void 
ParseArquivo::setUpgradeBomba()
{
	this->upgradeBomba = atoi(dados["upBomba"].c_str());
}

void 
ParseArquivo::setUpgradeEspiao()
{
	this->upgradeEspiao = atoi(dados["upEspiao"].c_str());
}

void 
ParseArquivo::setTipoFundo()
{
	const char* fundo = (const char*)dados["tipoFundo"].c_str();
	sscanf(fundo,"%c", &tipoFundo);
}

void 
ParseArquivo::setTipoBaseAliada()
{
	const char* base = (const char*)dados["tipoBaseAliada"].c_str();
	sscanf(base,"%c", &tipoBaseAliada);
}

void
ParseArquivo::setTipoBaseInimiga()
{
	const char* base = (const char*)dados["tipoBaseInimiga"].c_str();
	sscanf(base,"%c", &tipoBaseInimiga);
}

void
ParseArquivo::setDescricaoObjetivo()
{
	this->descricaoObjetivo = dados["descricaoObjetivo"];
}

void
ParseArquivo::setNumInfoVitoria()
{
	this->numInfoVitoria = atoi(dados["numInfoVitoria"].c_str());
}

char
ParseArquivo::getTipoObjetivo() const 
{
	return this->tipoObjetivo;
}

Vector2D 
ParseArquivo::getBaseAlidaPosicao() const 
{
	return this->baseAlidaPosicao;
}

Vector2D 
ParseArquivo::getBaseInimigaPosicao() const 
{
	return this->baseInimigaPosicao;
}

Vector2D 
ParseArquivo::getPontoVitoriaAliado() const 
{
	return this->pontoVitoriaAliado;
}

Vector2D 
ParseArquivo::getPontoVitoriaInimigo() const 
{
	return this->pontoVitoriaInimigo;
}

int 
ParseArquivo::getNumeroRecursoInicial() const 
{
	return this->numeroRecursoInicial;
}

int 
ParseArquivo::getCustoTorre() const 
{
	return this->custoTorre;
}

int 
ParseArquivo::getCustoBomba() const 
{
	return this->custoBomba;
}

int 
ParseArquivo::getCustoEspiao() const 
{
	return this->custoEspiao;
}

int 
ParseArquivo::getEvolucaoCustoTorre() const 
{
	return this->evolucaoCustoTorre;
}

int 
ParseArquivo::getEvolucaoCustoEspiao() const 
{
	return this->evolucaoCustoEspiao;
}

int 
ParseArquivo::getEvolucaoCustoBomba() const 
{
	return this->evolucaoCustoBomba;
}

int 
ParseArquivo::getUpgradeTorre() const 
{
	return this->upgradeTorre;
}

int 
ParseArquivo::getUpgradeBomba() const 
{
	return this->upgradeBomba;
}

int 
ParseArquivo::getUpgradeEspiao() const 
{
	return this->upgradeEspiao;
}

char 
ParseArquivo::getTipoFundo() const 
{
	return this->tipoFundo;
}

char 
ParseArquivo::getTipoBaseAliada() const 
{
	return this->tipoBaseAliada;
}

char 
ParseArquivo::getTipoBaseInimiga() const 
{
	return this->tipoBaseInimiga;
}

std::string 
ParseArquivo::getDescricaoObjetivo() const
{
	return this->descricaoObjetivo;
}

int 
ParseArquivo::getNumInfoVitoria() const
{
	return this->numInfoVitoria;
}
