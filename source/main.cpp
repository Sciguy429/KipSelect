#include <switch.h>
#include <string>

#include "gfx.h"
#include "error.h"
#include "menu.h"
#include "kip.h"
#include "bct.h"
#include "lfs.h"

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
	errorLoadAssets();
	menu.loadAssets();
	lfs.parseLFSDatabase();
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
	menuItem rebootItem;
	rebootItem.name = "Reboot";
	rebootItem.status = false;
	rebootItem.details.push_back(menuDetail());
	rebootItem.details[0].prefix = "Discription:\n";
	rebootItem.details[0].data = "Reboot the console from within this tool. Do not use this with exfat, it may cause corruption!";
	menu.addMenuItem(3, rebootItem);
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
				kip.setKIPItemEnabled(menu.getMenuSelected(), !kip.getKIPItemEnabled(menu.getMenuSelected()));
				menu.toggleSelected();
				menu.drawMenu();
				break;
			case 1:
				bct.setBCTItemEnabled(menu.getMenuSelected(), !bct.getBCTItemEnabled(menu.getMenuSelected()));
				menu.toggleSelected();
				menu.drawMenu();
				break;
			case 2:
				lfs.setLFSItemEnabled(menu.getMenuSelected(), !lfs.getLFSItemEnabled(menu.getMenuSelected()));
				menu.toggleSelected();
				menu.drawMenu();
				break;
			case 3:
				//NOTE: For now we will just reboot if 'a' is pressed as there is only one option here (More are to be added later on)
				bpcInitialize();
				bpcRebootSystem();
				break;
			default:
				break;
			}
		}
	}
	menu.destroyAssets();
	errorDestroyAssets();
	gfxCleanUp();
	romfsExit();
	socketExit();
	return 0;
}
