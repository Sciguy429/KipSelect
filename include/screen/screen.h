#pragma once

#include <switch.h>

#include "screen/scene.h"

class SCREEN {
public:
	SCREEN(unsigned int sizeX, unsigned int sizeY, u32 renderThreadCore);
private:
	unsigned int sizeX;
	unsigned int sizeY;
	u32 renderThreadCore;
	SCENE *mainScene;
};