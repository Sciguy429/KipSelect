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

unsigned int ANIMATION::getTextureIndexSelected() {
	return textureIndexSelected;
}

void ANIMATION::setTextureIndexSelected(unsigned int textureIndexSelected) {
	this->textureIndexSelected = textureIndexSelected;
}

trigger *ANIMATION::getRenderTrigger() {
	return renderTrigger;
}

void ANIMATION::setRenderTrigger(trigger *renderTrigger) {
	this->renderTrigger = renderTrigger;
}

ANIMATION::ANIMATION() {
	setType(OBJECT_TYPE_ANIMATION);
}