#include <algorithm>

#include "screen/scene.h"

struct objectFindId : std::unary_function<OBJECT, bool> {
	std::string id;
	objectFindId(std::string id) :id(id) { }
	bool operator()(OBJECT const& m) const {
		return m.getId() == id;
	}
};

struct sceneTextureFindPath : std::unary_function<sceneTexture, bool> {
	std::string path;
	sceneTextureFindPath(std::string path) :path(path) { }
	bool operator()(sceneTexture const& m) const {
		return m.path == path;
	}
};

struct sceneFontFindPath : std::unary_function<sceneFont, bool> {
	std::string path;
	sceneFontFindPath(std::string path) :path(path) { }
	bool operator()(sceneFont const& m) const {
		return m.path == path;
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
}

SCENE::~SCENE() {
	destroyLocalFonts();
	destroyLocalTextures();
}

font *SCENE::addLocalFont(const char *path) {
	std::vector<sceneFont>::iterator sceneFontItr = std::find_if(sceneFonts.begin(), sceneFonts.end(), sceneFontFindPath(path));
	if (sceneFontItr == sceneFonts.end()) {
		sceneFont sFnt;
		sFnt.path = path;
		sFnt.fnt = gfxCreateFontFromTTF(path);
		sceneFonts.push_back(sFnt);
		return sFnt.fnt;
	}
	return sceneFontItr->fnt;
}

void SCENE::destroyLocalFonts() {
	if (sceneFonts.empty()) {
		return;
	}
	for (std::size_t i = 0; i < sceneFonts.size(); i++) {
		gfxDestroyFont(sceneFonts[i].fnt);
	}
	sceneFonts.clear();
}

texture *SCENE::addLocalTexture(const char *path) {
	std::vector<sceneTexture>::iterator sceneTextureItr = std::find_if(sceneTextures.begin(), sceneTextures.end(), sceneTextureFindPath(path));
	if (sceneTextureItr == sceneTextures.end()) {
		sceneTexture sTex;
		sTex.path = path;
		sTex.tex = gfxCreateTextureFromPNG(path);
		sceneTextures.push_back(sTex);
		return sTex.tex;
	}
	return sceneTextureItr->tex;
}

void SCENE::destroyLocalTextures() {
	if (sceneTextures.empty()) {
		return;
	}
	for (std::size_t i = 0; i < sceneTextures.size(); i++) {
		gfxDestroyTexture(sceneTextures[i].tex);
	}
	sceneTextures.clear();
}