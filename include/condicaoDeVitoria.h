#ifndef CONDICAODEVITORIA_H
#define CONDICAODEVITORIA_H

class CondicaoDeVitoria {
public:

	virtual bool verificarSeVenceu(void **args, int numArgs) = 0;
	virtual bool iniciarCondicoesFase(void **args, int numArgs) = 0;

};

#endif
