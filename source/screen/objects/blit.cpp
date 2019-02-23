#include "screen/objects/blit.h"

texture *BLIT::getTexture(std::string id) {
	//Stub
}

void BLIT::addTexture(std::string id, texture *tex) {
	//Stub
}

std::string BLIT::getTextureSelected() {
	return textureSelected;
}

void BLIT::setTextureSelected(std::string textureSelected) {
	this->textureSelected = textureSelected;
}