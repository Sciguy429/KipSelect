#include <switch.h>

#include "error.h"
#include "load.h"

bool errorThrown = false;
regTex *errorBackground;
regFnt *fnt;

void errorRegisterAssets() {
	errorBackground = registerTexture("romfs:/png/error/error_background.png");
	fnt = registerFont("romfs:/font/bahnschrift.ttf");
}

bool isErrorThrown() {
	return errorThrown;
}

void errorThrow(const char *header, const char *info, const char *data) {
	errorThrown = true;
	gfxBlit(frameBuffer, errorBackground->tex, 0, 0);
	gfxDrawTextCenter(frameBuffer, header, fnt->fnt, 640, 280, 32, RGBA8(255, 255, 255, 0));
	while (!(hidKeysDown(CONTROLLER_P1_AUTO) & KEY_PLUS)) {
		hidScanInput();
		consoleUpdate(NULL);
	}
}