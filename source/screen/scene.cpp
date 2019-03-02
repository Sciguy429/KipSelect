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

bool stringToBool(bool *success, std::string str) {
	if (str == "false") {
		*success = true;
		return false;
	}
	else if (str == "true") {
		*success = true;
		return true;
	}
	else {
		*success = false;
		return false;
	}
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
		//Retrieve Object Name
		const char *objName = XMLCHAR_TO_CONSTCHAR(obj->name);
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
		//~~
		//Retrieve Object Static
		XPATHRESULT staticResult = layout.evalXPathExpFromNode(&success, obj, "static");
		if (!success) {
			printf("SCENE -- ERROR :: Unable To Find Static In Object #%d In Layout File: %s\n", i, layoutXMLFilePath);
			return;
		}
		if (staticResult.getNodeCount() != 1) {
			printf("SCENE -- ERROR :: Static Search In Object #%d Did Not Return 1 Result, %d Returned\n", i, staticResult.getNodeCount());
			return;
		}
		bool objStatic = stringToBool(&success, layout.getKeyword(staticResult.getNodePtr()[0]));
		if (!success) {
			printf("SCENE -- ERROR :: Static In Object %d Is Not Of Type 'bool'\n", i);
			return;
		}
		//~~
		//Retrieve Object Position (x)
		XPATHRESULT positionXResult = layout.evalXPathExpFromNode(&success, obj, "position/x");
		if (!success) {
			printf("SCENE -- ERROR :: Unable To Find Position (x) In Object #%d In Layout File: %s\n", i, layoutXMLFilePath);
			return;
		}
		if (positionXResult.getNodeCount() != 1) {
			printf("SCENE -- ERROR :: Position (x) Search In Object #%d Did Not Return 1 Result, %d Returned\n", i, positionXResult.getNodeCount());
			return;
		}
		unsigned int objPositionX = stringToUnsignedInt(&success, layout.getKeyword(positionXResult.getNodePtr()[0]));
		if (!success) {
			printf("SCENE -- ERROR :: Position (x) In Object #%d Is Not Of Type 'unsigned int'\n", i);
			return;
		}
		//~~
		//Retrieve Object Position (y)
		XPATHRESULT positionYResult = layout.evalXPathExpFromNode(&success, obj, "position/y");
		if (!success) {
			printf("SCENE -- ERROR :: Unable To Find Position (y) In Object #%d In Layout File: %s\n", i, layoutXMLFilePath);
			return;
		}
		if (positionYResult.getNodeCount() != 1) {
			printf("SCENE -- ERROR :: Position (y) Search In Object #%d Did Not Return 1 Result, %d Returned\n", i, positionYResult.getNodeCount());
			return;
		}
		unsigned int objPositionY = stringToUnsignedInt(&success, layout.getKeyword(positionYResult.getNodePtr()[0]));
		if (!success) {
			printf("SCENE -- ERROR :: Position (y) In Object #%d Is Not Of Type 'unsigned int'\n", i);
			return;
		}
		//~~
		//Retrieve Object Center Type
		XPATHRESULT centerTypeResult = layout.evalXPathExpFromNode(&success, obj, "position/centerType");
		if (!success) {
			printf("SCENE -- ERROR :: Unable To Find Center Type In Object #%d In Layout File: %s\n", i, layoutXMLFilePath);
			return;
		}
		if (centerTypeResult.getNodeCount() != 1) {
			printf("SCENE -- ERROR :: Center Type Search In Object #%d Did Not Return 1 Result, %d Returned\n", i, centerTypeResult.getNodeCount());
			return;
		}
		unsigned int objCenterType = stringToUnsignedInt(&success, layout.getKeyword(centerTypeResult.getNodePtr()[0]));
		if (!success) {
			printf("SCENE -- ERROR :: Center Type In Object #%d Is Not Of Type 'unsigned int'\n", i);
			return;
		}
		//~~
		//Retrieve Object Specific Data
		if (strcmp(objName, "text") == 0) {
			//Retrieve Text Font
			XPATHRESULT textFontPathResult = layout.evalXPathExpFromNode(&success, obj, "font");
			if (!success) {
				printf("SCENE -- ERROR :: Unable To Find Font In Text Object #%d In Layout File: %s\n", i, layoutXMLFilePath);
				return;
			}
			if (textFontPathResult.getNodeCount() != 1) {
				printf("SCENE -- ERROR :: Font Search In Text Object #%d Did Not Return 1 Result, %d Returned\n", i, textFontPathResult.getNodeCount());
				return;
			}
			std::string textObjFontPath = layout.getKeyword(textFontPathResult.getNodePtr()[0]);
			//~~
			//Retrieve Text Size
			XPATHRESULT textSizeResult = layout.evalXPathExpFromNode(&success, obj, "size");
			if (!success) {
				printf("SCENE -- ERROR :: Unable To Find Size In Text Object #%d In Layout File: %s\n", i, layoutXMLFilePath);
				return;
			}
			if (textSizeResult.getNodeCount() != 1) {
				printf("SCENE -- ERROR :: Size Search In Text Object #%d Did Not Return 1 Result, %d Returned\n", i, textSizeResult.getNodeCount());
				return;
			}
			unsigned int textObjSize = stringToUnsignedInt(&success, layout.getKeyword(textSizeResult.getNodePtr()[0]));
			if (!success) {
				printf("SCENE -- ERROR :: Size In Text Object #%d Is Not Of Type 'unsigned int'\n", i);
				return;
			}
			//~~
			//Retrieve Wrap
			XPATHRESULT textWrapResult = layout.evalXPathExpFromNode(&success, obj, "wrap");
			if (!success) {
				printf("SCENE -- ERROR :: Unable To Find Wrap In Text Object #%d In Layout File: %s\n", i, layoutXMLFilePath);
				return;
			}
			if (textWrapResult.getNodeCount() != 1) {
				printf("SCENE -- ERROR :: Wrap Search In Text Object #%d Did Not Return 1 Result, %d Returned\n", i, textWrapResult.getNodeCount());
				return;
			}
			unsigned int textObjWrap = stringToUnsignedInt(&success, layout.getKeyword(textWrapResult.getNodePtr()[0]));
			if (!success) {
				printf("SCENE -- ERROR :: Wrap In Text Object #%d Is Not Of Type 'unsigned int'\n", i);
				return;
			}
			//~~
			//Retrieve Text
			XPATHRESULT textTextResult = layout.evalXPathExpFromNode(&success, obj, "wrap");
			if (!success) {
				printf("SCENE -- ERROR :: Unable To Find Text In Text Object #%d In Layout File: %s\n", i, layoutXMLFilePath);
				return;
			}
			if (textTextResult.getNodeCount() != 1) {
				printf("SCENE -- ERROR :: Text Search In Text Object #%d Did Not Return 1 Result, %d Returned\n", i, textTextResult.getNodeCount());
				return;
			}
			std::string textObjText = layout.getKeyword(textTextResult.getNodePtr()[0]);
			//~~
			//Text Object Creation
			TEXT *textObj = new TEXT();
			textObj->setId(objId);
			textObj->setIsStatic(objStatic);
			textObj->setPosX(objPositionX);
			textObj->setPosY(objPositionY);
			textObj->setCenterType(objCenterType);
			//---
			font *textObjFont = addLocalFont(textObjFontPath.c_str());
			textObj->setFont(textObjFont);
			textObj->setSize(textObjSize);
			textObj->setWrap(textObjWrap);
			textObj->setText(textObjText);
			//~~
			sceneObjects.push_back(textObj);
		}
		else if (strcmp(objName, "blit") == 0) {
			//Retrieve Texture List
			XPATHRESULT blitTexturesResult = layout.evalXPathExpFromNode(&success, obj, "textures/texture");
			if (!success) {
				printf("SCENE -- ERROR :: Unable To Find Textures In Blit Object #%d In Layout File: %s\n", i, layoutXMLFilePath);
				return;
			}
			//~~
			//Retrieve Textures
			std::vector<blitTexture> blitObjTextures;
			for (unsigned int t = 0; t < blitTexturesResult.getNodeCount(); t++) {
				blitTexture blitTex;
				xmlNodePtr texObj = blitTexturesResult.getNodePtr()[t];
				//Retrieve Texture Id
				xmlChar *blitTextureIdXmlChar = xmlGetProp(obj, (xmlChar*) "id");
				if (blitTextureIdXmlChar == NULL) {
					printf("SCENE -- ERROR :: Blit Object #%d Texture #%d Is Missing A Id\n", i, t);
					return;
				}
				blitTex.id = XMLCHAR_TO_CONSTCHAR(blitTextureIdXmlChar);
				xmlFree(blitTextureIdXmlChar);
				//~~
				//Retrive Texture Path
				XPATHRESULT texPathResult = layout.evalXPathExpFromNode(&success, texObj, "path");
				if (!success) {
					printf("SCENE -- ERROR :: Unable To Find Path In Blit Object #%d Texture #%d\n", i, t);
					return;
				}
				if (texPathResult.getNodeCount() != 1) {
					printf("SCENE -- ERROR :: Blit Object #%d Texture #%d Path Search Did Not Return 1 Result, %d Returned\n", i, t, texPathResult.getNodeCount());
					return;
				}
				blitTex.tex = addLocalTexture(layout.getKeyword(texPathResult.getNodePtr()[0]).c_str());
				//~~
				blitObjTextures.push_back(blitTex);
			}
			//~~
			//Retrieve Texture Selected
			XPATHRESULT blitTextureSelectedResult = layout.evalXPathExpFromNode(&success, obj, "textureSelected");
			if (!success) {
				printf("SCENE -- ERROR :: Unable To Find Texture Selected In Blit Object #%d In Layout File: %s\n", i, layoutXMLFilePath);
				return;
			}
			if (blitTextureSelectedResult.getNodeCount() != 1) {
				printf("SCENE -- ERROR :: Texture Selected Search In Blit Object #%d Did Not Return 1 Result, %d Returned\n", i, blitTextureSelectedResult.getNodeCount());
				return;
			}
			std::string blitObjTextureSelected = layout.getKeyword(blitTextureSelectedResult.getNodePtr()[0]);
			//~~
			//Blit Object Creation
			BLIT *blitObject = new BLIT();
			blitObject->setId(objId);
			blitObject->setIsStatic(objStatic);
			blitObject->setPosX(objPositionX);
			blitObject->setPosY(objPositionY);
			blitObject->setCenterType(objCenterType);
			//---
			for (std::size_t t = 0; t < blitObjTextures.size(); t++) {
				blitObject->addTexture(blitObjTextures[t].id, blitObjTextures[t].tex);
			}
			blitObject->setTextureSelected(blitObjTextureSelected);
			//~~
			sceneObjects.push_back(blitObject);
		}
		else if (strcmp(objName, "animation") == 0) {
			//Animation Object Creation
			ANIMATION *animationObject = new ANIMATION();
			animationObject->setId(objId);
			animationObject->setIsStatic(objStatic);
			animationObject->setPosX(objPositionX);
			animationObject->setPosY(objPositionY);
			animationObject->setCenterType(objCenterType);
			//~~
			sceneObjects.push_back(animationObject);
		}
		else {
			printf("SCENE -- ERROR :: Object #%d Has A Unknown Type: %s\n", i, objName);
			return;
		}
		//~~
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