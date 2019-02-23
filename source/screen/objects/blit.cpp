#include <algorithm>

#include "screen/objects/blit.h"

struct texFindId : std::unary_function<blitTexture, bool> {
	std::string id;
	texFindId(std::string id) :id(id) { }
	bool operator()(blitTexture const& m) const {
		return m.id == id;
	}
};

texture *BLIT::getTexture(std::string id) const {
	std::vector<blitTexture>::iterator texItr = std::find_if(textures.begin(), textures.end(), texFindId(id));
	if (texItr == textures.end()) {
		return NULL;
	}
	else {
		return texItr->tex;
	}
}

void BLIT::addTexture(std::string id, texture *tex) {
	unsigned int pos = textures.size();
	textures.push_back(blitTexture());
	textures[pos].id = id;
	textures[pos].tex = tex;
}

std::string BLIT::getTextureSelected() const {
	return textureSelected;
}

void BLIT::setTextureSelected(std::string textureSelected) {
	this->textureSelected = textureSelected;
}