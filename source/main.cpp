#include <switch.h>
#include <string>

#include "console.h"
#include "gfx.h"
#include "kip.h"
#include "bct.h"

using namespace std;

bool run = true;
u64 kDown;

int main(int argc, char **argv) {
	KIP kip;
	BCT bct;
	romfsInit();
	gfxInit(1280, 720);
	//initLocalConsole();
	//log("Scanning For Kips", LOG_LEVEL_INFO);
	kip.scanForKip();
	//log(SSTR("Found " << kip.getKipCount() << " Kips"), LOG_LEVEL_INFO);
	//log("Reading BCT Values", LOG_LEVEL_INFO);
	bct.readBCT();
	//log(SSTR("Found " << bct.getBCTCount() << " BCT Values"), LOG_LEVEL_INFO);

	texture *backround = gfxCreateTextureFromPNG("romfs:/backround.png");
	gfxBlit(frameBuffer, backround, 0, 0, 0);
	gfxDestroyTexture(backround);

	gfxDrawPixel(frameBuffer, 0, 0, RGBA8(255, 0, 0, 0));
	gfxDrawPixel(frameBuffer, 100, 100, RGBA8(0, 255, 0, 0));
	gfxDrawLine(frameBuffer, 200, 200, 600, 600, RGBA8(0, 0, 255, 0));
	gfxDrawVerticalLine(frameBuffer, 500, 500, 100, RGBA8(255, 255, 0, 0));
	gfxDrawHorizontalLine(frameBuffer, 500, 500, 100, RGBA8(255, 0, 255, 0));
	gfxDrawRect(frameBuffer, 400, 300, 500, 350, RGBA8(255, 255, 0, 0), false);
	gfxDrawRect(frameBuffer, 550, 300, 650, 350, RGBA8(0, 255, 255, 0), true);
	gfxDrawRect(frameBuffer, 600, 325, 650, 350, RGBA8(255, 0, 0, 0), true);
	gfxDrawLine(frameBuffer, 0, 0, 1280 - 1, 720 - 1, RGBA8(255, 255, 255, 0));
	gfxDrawPixel(frameBuffer, 1280 - 1, 720 - 1, RGBA8(255, 0, 0, 0));

	texture *test = gfxCreateTexture(200, 200);
	gfxFill(test, RGBA8(0, 0, 255, 0));
	gfxDrawRect(test, 0, 0, 100, 100, RGBA8(255, 0, 0, 0), true);
	gfxDrawRect(test, 100, 100, 199, 199, RGBA8(0, 255, 0, 0), true);
	gfxBlit(frameBuffer, test, 600, 500, 0);
	gfxDestroyTexture(test);

	texture *icon = gfxCreateTextureFromPNG("romfs:/icon.png");
	gfxBlit(frameBuffer, icon, 1280 - 256, 720 - 256, 0);
	gfxDestroyTexture(icon);

	while (appletMainLoop() && run) {
		hidScanInput();
		kDown = hidKeysDown(CONTROLLER_P1_AUTO);
		if (kDown & KEY_PLUS) {
			run = false;
		}
		if (kDown & KEY_A) {
			gfxHandelBuffers();
		}
		consoleUpdate(NULL);
	}
	gfxCleanUp();
	romfsExit();
	consoleExit(NULL);
	return 0;
}