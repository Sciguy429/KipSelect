#include <algorithm>

#include "screen/scene.h"
#include "utils/xml.h"

struct objectFindId : std::unary_function<void *, bool> {
	std::string id;
	objectFindId(std::string id) :id(id) { }
	bool operator()(void * const& m) const {
		return static_cast<OBJECT *>(m)->getId() == id;
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

void *SCENE::getObjectVector(const char *objectId) {
	if (sceneObjects.empty()) {
		return NULL;
	}
	std::vector<void *>::iterator sceneObjectItr = std::find_if(sceneObjects.begin(), sceneObjects.end(), objectFindId(objectId));
	if (sceneObjectItr == sceneObjects.end()) {
		return NULL;
	}
	return *sceneObjectItr;
}

SCENE::SCENE(const char *layoutXMLFilePath) {
	bool success;
	XML layout(&success, layoutXMLFilePath);
	if (!success) {
		printf("SCENE -- Failed To Parse Layout Xml File: %s\n", layoutXMLFilePath);
		return;
	}
	XPATHRESULT sizeXResult = layout.evalXPathExp(&success, "/scene/size/x");
	if (!success) {
		printf("SCENE -- Unable To Find Size (x) In Layout File: %s\n", layoutXMLFilePath);
		return;
	}
	XPATHRESULT sizeYResult = layout.evalXPathExp(&success, "/scene/size/y");
	XPATHRESULT backgroundRedResult = layout.evalXPathExp(&success, "/scene/backgroundColor/red");
	XPATHRESULT backgroundGreenResult = layout.evalXPathExp(&success, "/scene/backgroundColor/green");
	XPATHRESULT backgroundBlueResult = layout.evalXPathExp(&success, "/scene/backgroundColor/blue");
	XPATHRESULT objectsResult = layout.evalXPathExp(&success, "/scene/objects/*");
}

SCENE::~SCENE() {
	if (!sceneObjects.empty()) {
		for (unsigned int i = 0; i < sceneObjects.size(); i++) {
			switch (getObjectType(sceneObjects[i])) {
			case OBJECT_TYPE_GENERIC: {
				OBJECT *object = (OBJECT*)sceneObjects[i];
				delete object;
				break;
			}
			case OBJECT_TYPE_TEXT: {
				TEXT *text = (TEXT*)sceneObjects[i];
				delete text;
				break;
			}
			case OBJECT_TYPE_BLIT: {
				BLIT *blit = (BLIT*)sceneObjects[i];
				delete blit;
				break;
			}
			case OBJECT_TYPE_ANIMATION: {
				ANIMATION *animation = (ANIMATION*)sceneObjects[i];
				delete animation;
				break;
			}
			}
		}
	}
	destroyLocalFonts();
	destroyLocalTextures();
}

unsigned int SCENE::getObjectType(void *objectPtr) {
	OBJECT *obj = (OBJECT*)objectPtr;
	return obj->getType();
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