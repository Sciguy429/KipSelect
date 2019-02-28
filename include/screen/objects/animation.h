#pragma once

#include <string>
#include <vector>

#include "screen/gfx.h"
#include "screen/objects/object.h"

class ANIMATION : public OBJECT {
public:
	bool getEnabled();
	void setEnabled(bool enabled);
	unsigned int getFPS();
	void setFPS(unsigned int fps);
	unsigned int getTextureCount();
	texture *getTexture(unsigned int index);
	void addTexture(texture *tex);
	unsigned int getTextureSelected();
	void setTextureSelected(unsigned int textureSelected);
	ANIMATION();
private:
	bool enabled;
	unsigned int fps;
	std::vector<texture*> textures;
	unsigned int textureSelected;
};