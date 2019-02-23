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
	TEXT *getTextObjectVector(const char *textObjectId);
	BLIT *getBlitObjectVector(const char *blitObjectId);
	//LIST getListIbjectVector(const char *listObjectId);
	SCENE(const char *layoutXMLFilePath);
private:
	std::vector<TEXT> textObjects;
	std::vector<BLIT> blitObjects;
	std::vector<sceneFont> fonts;
	std::vector<sceneTexture> textures;
};