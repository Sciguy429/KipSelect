#pragma once

#include <string>

#include "gfx.h"

typedef struct {
	std::string path;
	texture *tex;
} regTex;

typedef struct {
	std::string path;
	font *fnt;
} regFnt;

regTex *registerTexture(std::string path);

regFnt *registerFont(std::string path);

void loadRegisteredAssets();

void destroyRegisteredAssets();