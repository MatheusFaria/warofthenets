#ifndef FASE01_H
#define FASE01_H

#include "condicaodevitoria.h"

class Fase01 : public CondicaoDeVitoria {

public:

	virtual bool verificarSeVenceu(void **args, int);
	virtual bool iniciarCondicoes(void **args, int);
};

#endif