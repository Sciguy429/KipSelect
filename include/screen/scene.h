#pragma once

#include <string>
#include <vector>

#include "screen/gfx.h"
#include "screen/objects/object.h"
#include "screen/objects/text.h"
#include "screen/objects/blit.h"

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
	TEXT *getTextObjectVector(const char *textObjectId);
	BLIT *getBlitObjectVector(const char *blitObjectId);
	//LIST getListObjectVector(const char *listObjectId);
	SCENE(const char *layoutXMLFilePath);
	~SCENE();
private:
	font *addLocalFont(const char *path);
	void destroyLocalFonts();
	texture *addLocalTexture(const char *path);
	void destroyLocalTextures();
	unsigned int sizeX;
	unsigned int sizeY;
	unsigned int backgroundRed;
	unsigned int backgroundGreen;
	unsigned int backgroundBlue;
	std::vector<TEXT> textObjects;
	std::vector<BLIT> blitObjects;
	std::vector<sceneFont> sceneFonts;
	std::vector<sceneTexture> sceneTextures;
};