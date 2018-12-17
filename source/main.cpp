#include <switch.h>
#include <string>

#include "gfx.h"
#include "kip.h"
#include "bct.h"
#include "menu.h"

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
		menu.addMenuItem(0, kip.getKipName(i), "", "", "", kip.getKipName(i), kip.getKipValue(i));
	}
	for (int i = 0; i < bct.getBCTCount(); i++) {
		menu.addMenuItem(1, bct.getBCTName(i), "", "", "", bct.getBCTName(i), bct.getBCTValue(i));
	}
	menu.addMenuItem(2, "TEST ITEM 1", "9f06243abcb89c70e0c331c61d871fa7", "1.2.1", "This is a test of a discription", "", true);
	menu.addMenuItem(2, "TEST ITEM 2", "9f06243abcb89c70e0c331c61d871fa7", "1.2.1", "", "", false);
	menu.addMenuItem(2, "TEST ITEM 3", "9f06243abcb89c70e0c331c61d871fa7", "0.0.0", "", "", true);
	menu.addMenuItem(2, "TEST ITEM 4", "9f06243abcb89c70e0c331c61d871fa7", "7.6.4", "", "", true);
	menu.drawMenu();
	while (appletMainLoop() && run) {
		hidScanInput();
		kDown = hidKeysDown(CONTROLLER_P1_AUTO);
		if (kDown & KEY_PLUS) {
			run = false;
		}
		else if (kDown & KEY_L) {
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
		else if (kDown & KEY_UP) {
			if (menu.getMenuSelected() > 0) {
				menu.setMenuSelected(menu.getMenuSelected() - 1);
				menu.drawMenu();
			}
		}
		else if (kDown & KEY_DOWN) {
			if (menu.getMenuSelected() < menu.getMenuSize() - 1) {
				menu.setMenuSelected(menu.getMenuSelected() + 1);
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