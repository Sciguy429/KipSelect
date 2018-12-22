#include <switch.h>
#include <string>

#include "gfx.h"
#include "load.h"
#include "error.h"
#include "menu.h"
#include "kip.h"
#include "bct.h"
#include "lfs.h"

bool run = true;
u64 kDown;

int main(int argc, char **argv) {
	MENU menu;
	KIP kip;
	BCT bct;
	LFS lfs;
	socketInitializeDefault();
	nxlinkStdio();
	romfsInit();
	gfxInit(1280, 720);
	errorRegisterAssets();
	menu.registerAssets();
	loadRegisteredAssets();
	menu.init();
	kip.scanKIP();
	bct.scanBCT();
	lfs.scanLFS();
	for (unsigned int i = 0; i < kip.getKIPItemCount(); i++) {
		menu.addMenuItem(0, kip.getKIPMenuItem(i));
	}
	for (unsigned int i = 0; i < bct.getBCTItemCount(); i++) {
		menu.addMenuItem(1, bct.getBCTMenuItem(i));
	}
	for (unsigned int i = 0; i < lfs.getLFSCount(); i++) {
		menu.addMenuItem(2, lfs.getLFSMenuItem(i));
	}
	//TMP (Test Code)
	for (unsigned int i = 0; i < lfs.getLFSCount(); i++) {
		menu.addMenuItem(2, lfs.getLFSMenuItem(i));
	}
	for (unsigned int i = 0; i < lfs.getLFSCount(); i++) {
		menu.addMenuItem(2, lfs.getLFSMenuItem(i));
	}
	//~~
	menu.drawMenu();
	while (appletMainLoop() && !isErrorThrown()) {
		hidScanInput();
		kDown = hidKeysDown(CONTROLLER_P1_AUTO);
		if (kDown & KEY_PLUS) {
			break;
		}
		else if (kDown & KEY_L) {
			if (menu.getTabSelected() > 0) {
				menu.setTabSelected(menu.getTabSelected() - 1);
				menu.drawMenu();
			}
		}
		else if (kDown & KEY_R) {
			if (menu.getTabSelected() < 3) {
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
		else if (kDown & KEY_A) {
			switch (menu.getTabSelected()) {
			case 0:
				menu.toggleSelected();
				menu.drawMenu();
				break;
			case 1:
				menu.toggleSelected();
				menu.drawMenu();
				break;
			case 2:
				menu.toggleSelected();
				menu.drawMenu();
				break;
			case 3:
				errorThrow("Example Error", "Sample description\n%s", "SAMPLE TEXT");
				break;
			default:
				break;
			}
		}
		consoleUpdate(NULL);
	}
	destroyRegisteredAssets();
	gfxCleanUp();
	romfsExit();
	socketExit();
	consoleExit(NULL);
	return 0;
}
