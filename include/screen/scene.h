#pragma once

#include <string>
#include <vector>

#include "screen/gfx.h"
#include "screen/objects/object.h"
#include "screen/objects/text.h"
#include "screen/objects/blit.h"
#include "screen/objects/animation.h"

typedef struct {
	std::string path;
	font *fnt;
} sceneFont;

typedef struct {
	std::string path;
	texture *tex;
} sceneTexture;

class SCENE {
public:
	unsigned int getSizeX();
	void setSizeX(unsigned int sizeX);
	unsigned int getSizeY();
	void setSizeY(unsigned int sizeY);
	unsigned int getBackgroundRed();
	void setBackgroundRed(unsigned int backgroundRed);
	unsigned int getBackgroundGreen();
	void setBackgroundGreen(unsigned int backgroundGreen);
	unsigned int getBackgroundBlue();
	void setBackgroundBlue(unsigned int backgroundBlue);
	void *getObjectVector(const char *objectId);
	SCENE(const char *layoutXMLFilePath);
	~SCENE();
private:
	unsigned int getObjectType(void *objectPtr);
	font *addLocalFont(const char *path);
	void destroyLocalFonts();
	texture *addLocalTexture(const char *path);
	void destroyLocalTextures();
	unsigned int sizeX;
	unsigned int sizeY;
	unsigned int backgroundRed;
	unsigned int backgroundGreen;
	unsigned int backgroundBlue;
	std::vector<void *> sceneObjects;
	std::vector<sceneFont> sceneFonts;
	std::vector<sceneTexture> sceneTextures;
};