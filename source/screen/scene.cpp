#include <algorithm>

#include "screen/scene.h"

struct objectFindId : std::unary_function<OBJECT, bool> {
	std::string id;
	objectFindId(std::string id) :id(id) { }
	bool operator()(OBJECT const& m) const {
		return m.getId() == id;
	}
};

unsigned int SCENE::getSizeX() {
	return sizeX;
}

void SCENE::setSizeX(unsigned int sizeX) {
	this->sizeX = sizeX;
}

unsigned int SCENE::getSizeY() {
	return sizeY;
}

void SCENE::setSizeY(unsigned int sizeY) {
	this->sizeY = sizeY;
}

unsigned int SCENE::getBackgroundRed() {
	return backgroundRed;
}

void SCENE::setBackgroundRed(unsigned int backgroundRed) {
	this->backgroundRed = backgroundRed;
}

unsigned int SCENE::getBackgroundGreen() {
	return backgroundGreen;
}

void SCENE::setBackgroundGreen(unsigned int backgroundGreen) {
	this->backgroundGreen = backgroundGreen;
}

unsigned int SCENE::getBackgroundBlue() {
	return backgroundBlue;
}

void SCENE::setBackgroundBlue(unsigned int backgroundBlue) {
	this->backgroundBlue = backgroundBlue;
}

TEXT *SCENE::getTextObjectVector(const char *textObjectId) {
	if (textObjects.empty()) {
		return NULL;
	}
	std::vector<TEXT>::iterator textObjectItr = std::find_if(textObjects.begin(), textObjects.end(), objectFindId(textObjectId));
	if (textObjectItr == textObjects.end()) {
		return NULL;
	}
	return &*textObjectItr;
}

BLIT *SCENE::getBlitObjectVector(const char *blitObjectId) {
	if (blitObjects.empty()) {
		return NULL;
	}
	std::vector<BLIT>::iterator blitObjectItr = std::find_if(blitObjects.begin(), blitObjects.end(), objectFindId(blitObjectId));
	if (blitObjectItr == blitObjects.end()) {
		return NULL;
	}
	return &*blitObjectItr;
}

SCENE::SCENE(const char *layoutXMLFilePath) {
	//Stub
	TEXT testText;
	testText.setId("test");
	testText.setText("NO U");
	testText.setSize(10);
	textObjects.push_back(testText);
	TEXT testText2;
	testText2.setId("nop");
	testText2.setText("test");
	testText2.setSize(16);
	textObjects.push_back(testText2);
}