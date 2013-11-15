#include "base.h"
#include "texturemanager.h"
#include "render.h"

Base::Base(int tipoBase, int informacoesPorTurno, int x, int y) : Torre(tipoBase, 1, x, y, "resources/img/base.png")
{
	this->informacoesPorTurno = informacoesPorTurno;
	numFrames = 1;
	numLevels = 1;
}

int 
Base::getInformacao()
{
	return this->informacoesPorTurno;
}

void 
Base::update()
{

}

void
Base::draw()
{
	TextureManager::Instance()->draw(imageId, (Uint32)position.getX(),(Uint32)position.getY(), 
		Render::getInstance()->getRenderer());
}