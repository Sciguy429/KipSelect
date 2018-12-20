#include <switch.h>
#include <string>

#include "gfx.h"
#include "kip.h"
#include "bct.h"
#include "lfs.h"
#include "menu.h"

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
	kip.scanForKip();
	bct.readBCT();
	lfs.scanLFS();
	menu.init();
	for (int i = 0; i < kip.getKipCount(); i++) {
		//TODO: Set up details
		std::vector<menuDetail> dets;
		menu.addMenuItem(0, kip.getKipName(i), dets, kip.getKipValue(i));
	}
	for (int i = 0; i < bct.getBCTCount(); i++) {
		//TODO: Set up details
		std::vector<menuDetail> dets;
		menu.addMenuItem(1, bct.getBCTName(i), dets, bct.getBCTValue(i));
	}
	for (int i = 0; i < lfs.getLFSCount(), i++) {
		//menu.addMenuItem(2, lfs.getLFSMenuItem(i));
	}
	//TEMPORARY
	std::vector<menuDetail> dets;
	dets.push_back(menuDetail());
	dets[0].data = "Feature Commming Soon!";
	dets.push_back(menuDetail());
	dets[1].data = ":D";
	menu.addMenuItem(2, "Feature Planned", dets, false);
	menu.addMenuItem(3, "Feature Planned", dets, false);
	//~~
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
		else if (kDown & KEY_A) {
			switch (menu.getTabSelected()) {
			case 0:
				kip.setKip(menu.getMenuSelected(), !kip.getKipValue(menu.getMenuSelected()));
				menu.toggleSelected();
				menu.drawMenu();
				break;
			case 1:
				bct.setBCT(menu.getMenuSelected(), !bct.getBCTValue(menu.getMenuSelected()));
				menu.toggleSelected();
				menu.drawMenu();
				break;
			case 2:
				menu.toggleSelected();
				menu.drawMenu();
				break;
			case 3:
				//Options
				break;
			default:
				break;
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
