#include <switch.h>

#include "error.h"
#include "gfx.h"

bool errorThrown = false;
texture *errorBackground;
font *fnt;

void errorLoadAssets() {
	errorBackground = gfxCreateTextureFromPNG("romfs:/png/error/error_background.png");
	fnt = gfxCreateFontFromTTF("romfs:/font/tt0288m_.ttf");
}

bool isErrorThrown() {
	return errorThrown;
}

void errorThrow(const char *header, const char *info, const char *data) {
	errorThrown = true;
	gfxBlit(frameBuffer, errorBackground, 0, 0);
	gfxDrawTextCenter(frameBuffer, header, fnt, 640, 280, 32, RGBA8(255, 255, 255, 0));
	while (!(hidKeysDown(CONTROLLER_P1_AUTO) & KEY_PLUS)) {
		hidScanInput();
		consoleUpdate(NULL);
	}
}

void errorDestroyAssets() {
	gfxDestroyTexture(errorBackground);
	gfxDestroyFont(fnt);
}
