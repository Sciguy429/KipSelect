#pragma once

#include <string>
#include <vector> 

#include "screen/gfx.h"
#include "screen/objects/object.h"

typedef struct {
	std::string id;
	texture *tex;
} blitTexture;

class BLIT: public OBJECT {
public:
	texture *getTexture(std::string id);
	void addTexture(std::string id, texture *tex);
	std::string getTextureSelected();
	void setTextureSelected(std::string textureSelected);
	BLIT();
private:
	std::vector<blitTexture> textures;
	std::string textureSelected;
};