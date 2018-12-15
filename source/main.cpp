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
	gfxInit(1280, 720);
	initLocalConsole();
	log("Scanning For Kips", LOG_LEVEL_INFO);
	kip.scanForKip();
	log(SSTR("Found " << kip.getKipCount() << " Kips"), LOG_LEVEL_INFO);
	log("Reading BCT Values", LOG_LEVEL_INFO);
	bct.readBCT();
	log(SSTR("Found " << bct.getBCTCount() << " BCT Values"), LOG_LEVEL_INFO);

	gfxDrawPixel(0, 0, RGBA8(255, 0, 0, 0));
	gfxDrawPixel(100, 100, RGBA8(0, 255, 0, 0));
	gfxDrawLine(200, 200, 600, 600, RGBA8(0, 0, 255, 0));
	gfxDrawVerticalLine(500, 500, 100, RGBA8(255, 255, 0, 0));
	gfxDrawHorizontalLine(500, 500, 100, RGBA8(255, 0, 255, 0));
	gfxDrawRect(400, 300, 500, 350, RGBA8(255, 255, 0, 0), false);
	gfxDrawRect(550, 300, 650, 350, RGBA8(0, 255, 255, 0), true);
	gfxDrawLine(0, 0, 1280 - 1, 720 - 1, RGBA8(255, 255, 255, 0));

	while (appletMainLoop && run) {
		hidScanInput();
		kDown = hidKeysDown(CONTROLLER_P1_AUTO);
		if (kDown & KEY_PLUS) {
			run = false;
		}
		consoleUpdate(NULL);
	}
	consoleExit(NULL);
	return 0;
}