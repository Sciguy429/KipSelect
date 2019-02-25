#pragma once

#include "screen/scene.h"

typedef struct {
	bool runThread;
	SCENE *mainScene;
	//SCENE *overlayScene;
} renderThreadControlVector;

void renderThread(void *vector);