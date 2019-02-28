#include "screen/objects/animation.h"

bool ANIMATION::getEnabled() {
	return enabled;
}

void ANIMATION::setEnabled(bool enabled) {
	this->enabled = enabled;
}

unsigned int ANIMATION::getFPS() {
	return fps;
}

void ANIMATION::setFPS(unsigned int fps) {
	this->fps = fps;
}

unsigned int ANIMATION::getTextureCount() {
	return textures.size();
}

texture *ANIMATION::getTexture(unsigned int index) {
	if (textures.empty() || index >= textures.size()) {
		return NULL;
	}
	return textures[index];
}

void ANIMATION::addTexture(texture *tex) {
	textures.push_back(tex);
}

unsigned int ANIMATION::getTextureSelected() {
	return textureSelected;
}

void ANIMATION::setTextureSelected(unsigned int textureSelected) {
	this->textureSelected = textureSelected;
}

ANIMATION::ANIMATION() {
	setType(OBJECT_TYPE_ANIMATION);
}