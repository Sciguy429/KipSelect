#include "screen/screen.h"

SCREEN::SCREEN(unsigned int sizeX, unsigned int sizeY, u32 renderThreadCore) {
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	this->renderThreadCore = renderThreadCore;
}