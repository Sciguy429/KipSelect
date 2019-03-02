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

unsigned int stringToUnsignedInt(bool *success, std::string str) {
	if (!std::all_of(str.begin(), str.end(), ::isdigit)) {
		*success = false;
		return 0;
	}
	*success = true;
	return std::stoul(str);
}

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
		printf("SCENE -- ERROR :: Failed To Parse Layout Xml File: %s\n", layoutXMLFilePath);
		return;
	}
	//Retrieve X Size
	XPATHRESULT sizeXResult = layout.evalXPathExp(&success, "/scene/size/x");
	if (!success) {
		printf("SCENE -- ERROR :: Unable To Find Size (x) In Layout File: %s\n", layoutXMLFilePath);
		return;
	}
	if (sizeXResult.getNodeCount() != 1) {
		printf("SCENE -- ERROR :: Size (x) Search Did Not Return 1 Result, %d Returned\n", sizeXResult.getNodeCount());
		return;
	}
	sizeX = stringToUnsignedInt(&success, layout.getKeyword(sizeXResult.getNodePtr()[0]));
	if (!success) {
		printf("SCENE -- ERROR :: Size (x) Is Not Of Type 'unsigned int'\n");
		return;
	}
	if (sizeX == 0) {
		printf("SCENE -- ERROR :: Size (x) Is 0\n");
		return;
	}
	//~~
	//Retrieve Y Size
	XPATHRESULT sizeYResult = layout.evalXPathExp(&success, "/scene/size/y");
	if (!success) {
		printf("SCENE -- ERROR :: Unable To Find Size (y) In Layout File: %s\n", layoutXMLFilePath);
		return;
	}
	if (sizeYResult.getNodeCount() != 1) {
		printf("SCENE -- ERROR :: Size (y) Search Did Not Return 1 Result, %d Returned\n", sizeYResult.getNodeCount());
		return;
	}
	sizeY = stringToUnsignedInt(&success, layout.getKeyword(sizeYResult.getNodePtr()[0]));
	if (!success) {
		printf("SCENE -- ERROR :: Size (y) Is Not Of Type 'unsigned int'\n");
		return;
	}
	if (sizeY == 0) {
		printf("SCENE -- ERROR :: Size (y) Is 0\n");
		return;
	}
	//~~
	//Retrieve Background Red
	XPATHRESULT backgroundRedResult = layout.evalXPathExp(&success, "/scene/backgroundColor/red");
	if (!success) {
		printf("SCENE -- ERROR :: Unable To Find Background Color Red In Layout File: %s\n", layoutXMLFilePath);
		return;
	}
	if (backgroundRedResult.getNodeCount() != 1) {
		printf("SCENE -- ERROR :: Background Color Red Search Did Not Return 1 Result, %d Returned\n", backgroundRedResult.getNodeCount());
		return;
	}
	backgroundRed = stringToUnsignedInt(&success, layout.getKeyword(backgroundRedResult.getNodePtr()[0]));
	if (!success) {
		printf("SCENE -- ERROR :: Background Color Red Is Not Of Type 'unsigned int'\n");
		return;
	}
	if (backgroundRed > 255) {
		printf("SCENE -- ERROR :: Background Color Red Is Larger Than 255, Value Is %d\n", backgroundRed);
		return;
	}
	//~~
	//Retrieve Background Green
	XPATHRESULT backgroundGreenResult = layout.evalXPathExp(&success, "/scene/backgroundColor/green");
	if (!success) {
		printf("SCENE -- ERROR :: Unable To Find Background Color Green In Layout File: %s\n", layoutXMLFilePath);
		return;
	}
	if (backgroundGreenResult.getNodeCount() != 1) {
		printf("SCENE -- ERROR :: Background Color Green Search Did Not Return 1 Result, %d Returned\n", backgroundGreenResult.getNodeCount());
		return;
	}
	backgroundGreen = stringToUnsignedInt(&success, layout.getKeyword(backgroundGreenResult.getNodePtr()[0]));
	if (!success) {
		printf("SCENE -- ERROR :: Background Color Green Is Not Of Type 'unsigned int'\n");
		return;
	}
	if (backgroundGreen > 255) {
		printf("SCENE -- ERROR :: Background Color Green Is Larger Than 255, Value Is %d\n", backgroundGreen);
		return;
	}
	//~~
	//Retrieve Background Blue
	XPATHRESULT backgroundBlueResult = layout.evalXPathExp(&success, "/scene/backgroundColor/blue");
	if (!success) {
		printf("SCENE -- ERROR :: Unable To Find Background Color Blue In Layout File: %s\n", layoutXMLFilePath);
		return;
	}
	if (backgroundBlueResult.getNodeCount() != 1) {
		printf("SCENE -- ERROR :: Background Color Blue Search Did Not Return 1 Result, %d Returned\n", backgroundBlueResult.getNodeCount());
		return;
	}
	backgroundBlue = stringToUnsignedInt(&success, layout.getKeyword(backgroundBlueResult.getNodePtr()[0]));
	if (!success) {
		printf("SCENE -- ERROR :: Background Color Blue Is Not Of Type 'unsigned int'\n");
		return;
	}
	if (backgroundBlue > 255) {
		printf("SCENE -- ERROR :: Background Color Blue Is Larger Than 255, Value Is %d\n", backgroundBlue);
		return;
	}
	//Retrieve Objects
	XPATHRESULT objectsResult = layout.evalXPathExp(&success, "/scene/objects/*");
	if (!success) {
		printf("SCENE -- ERROR :: Unable To Find Any Objects In Layout File: %s\n", layoutXMLFilePath);
		return;
	}
	for (unsigned int i = 0; i < objectsResult.getNodeCount(); i++) {
		xmlNodePtr obj = objectsResult.getNodePtr()[i];
		//Retrieve Object Type
		const char *objType = XMLCHAR_TO_CONSTCHAR(obj->name);
		//~~
		//Retrieve Object Id
		xmlChar *objIdXmlChar = xmlGetProp(obj, (xmlChar*) "id");
		std::string objId;
		if (objIdXmlChar == NULL) {
			printf("SCENE -- WARN :: Object #%d In Layout Is Missing A Id\n", i);
			objId = "__NOID__";
		}
		else {
			objId = XMLCHAR_TO_CONSTCHAR(objIdXmlChar);
			xmlFree(objIdXmlChar);
		}
		XPATHRESULT staticResult = layout.evalXPathExpFromNode(&success, obj, "static");
		printf("SCENE -- %d\n", staticResult.getNodeCount());
	}
	//~~
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