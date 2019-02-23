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
	texture *getTexture(std::string id) const;
	void addTexture(std::string id, texture *tex);
	std::string getTextureSelected() const;
	void setTextureSelected(std::string textureSelected);
private:
	std::vector<blitTexture> textures;
	std::string textureSelected;
};