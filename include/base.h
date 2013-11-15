#ifndef BASE_H
#define BASE_H

#include "torre.h"

class Base : public Torre{

public:

	Base(int tipoBase, int informacoesPorTurno, int x, int y);
	virtual int getInformacao();

	virtual void update();
	virtual void draw();

private:

	int informacoesPorTurno;

};


#endif