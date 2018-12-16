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
	socketInitializeDefault();
	nxlinkStdio();
	gfxInit(1280, 720);

	kip.scanForKip();
	bct.readBCT();

	menu.init();
	menu.addTab("Kip");
	menu.addTab("BCT.ini");
	for (int i = 0; i < kip.getKipCount(); i++) {
		menu.addOpt(0, kip.getKipName(i));
	}
	menu.drawMenu();

	while (appletMainLoop() && run) {
		hidScanInput();
		kDown = hidKeysDown(CONTROLLER_P1_AUTO);
		if (kDown & KEY_PLUS) {
			run = false;
		}
		if (kDown & KEY_A) {
			menu.resetMenu();
			menu.drawMenu();
		}
		consoleUpdate(NULL);
	}
	menu.destroyAssets();
	gfxCleanUp();
	romfsExit();
	socketExit();
	consoleExit(NULL);
	return 0;
}