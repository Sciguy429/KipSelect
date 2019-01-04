#include <switch.h>
#include <stdarg.h>

#include "error.h"
#include "gfx.h"

bool errorThrown = false;
texture *errorBackground;
font *fnt;

errorStructure errors[] = {
	{"Unable To Create Dirrectory", "The program was unable to create a dirrectory on the SD card!"}, //Mkdir Error
	{"File Move Failed", "The program was unable to move a file!"}, //Rename Error
	{"Unable To Open File", "The program was unable to open a file on the SD card in order to write to it!"}, //Ofstream Error
	{"Missing String In BCT.ini", "The program could not find a target setting previously found in bct.ini!"} //BCT Location Not Found Error
};

void errorLoadAssets() {
	errorBackground = gfxCreateTextureFromPNG("romfs:/png/error/error_background.png");
	fnt = gfxCreateFontFromTTF("romfs:/font/tt0288m_.ttf");
}

bool isErrorThrown() {
	return errorThrown;
}

void errorThrow(unsigned int errorType) {
	errorThrown = true;
	gfxBlit(frameBufferTexture, errorBackground, 0, 0);
	gfxDrawTextCenter(frameBufferTexture, errors[errorType].header.c_str(), fnt, 640, 140, 32, RGBA8(255, 255, 255, 0));
	gfxDrawTextWrap(frameBufferTexture, errors[errorType].info.c_str(), fnt, 40, 280, 32, RGBA8(255, 255, 255, 0), 1200);
	while (!(hidKeysDown(CONTROLLER_P1_AUTO) & KEY_PLUS)) {
		hidScanInput();
		consoleUpdate(NULL);
	}
}

void errorDestroyAssets() {
	gfxDestroyTexture(errorBackground);
	gfxDestroyFont(fnt);
}
