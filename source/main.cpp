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

	kip.scanForKip();
	bct.readBCT();

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