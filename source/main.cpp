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