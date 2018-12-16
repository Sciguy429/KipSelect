#include <switch.h>
#include <string>

#include "gfx.h"
#include "kip.h"
#include "bct.h"
#include "menu.h"

using namespace std;

bool run = true;
u64 kDown;

int main(int argc, char **argv) {
	MENU menu;
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

	menu.init();

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
	menu.destroyAssets();
	gfxCleanUp();
	romfsExit();
	consoleExit(NULL);
	return 0;
}