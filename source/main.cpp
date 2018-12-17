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
	socketInitializeDefault();
	nxlinkStdio();
	romfsInit();
	gfxInit(1280, 720);
	kip.scanForKip();
	bct.readBCT();
	menu.init();
	for (int i = 0; i < kip.getKipCount(); i++) {
		menu.addKipItem(kip.getKipName(i), "", "", kip.getKipName(i), kip.getKipValue(i));
	}
	for (int i = 0; i < bct.getBCTCount(); i++) {
		menu.addBCTItem(bct.getBCTName(i), "", "", bct.getBCTName(i), bct.getBCTValue(i));
	}
	menu.addLayeredFSItem("TEST ITEM", "", "", "", true);
	menu.drawMenu();
	while (appletMainLoop() && run) {
		hidScanInput();
		kDown = hidKeysDown(CONTROLLER_P1_AUTO);
		if (kDown & KEY_PLUS) {
			run = false;
		}
		//START HID
		if (kDown & KEY_L) {
			if (menu.getTabSelected() > 0) {
				menu.setMenuSelected(0);
				menu.setTabSelected(menu.getTabSelected() - 1);
				menu.drawMenu();
			}
		}
		else if (kDown & KEY_R) {
			if (menu.getTabSelected() < 3) {
				menu.setMenuSelected(0);
				menu.setTabSelected(menu.getTabSelected() + 1);
				menu.drawMenu();
			}
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