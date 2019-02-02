#include <switch.h>

#include "gfx.h"
#include "error.h"
#include "menu.h"
#include "kip.h"
#include "bct.h"
#include "lfs.h"
#include "reboot.h"

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
	lfs.parseSysDatabase();
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
	menuItem rebootAtmosphereItem;
	rebootAtmosphereItem.name = "Reboot To Atmosphere";
	rebootAtmosphereItem.status = false;
	rebootAtmosphereItem.details.push_back(menuDetail());
	rebootAtmosphereItem.details[0].prefix = "Discription:\n";
	rebootAtmosphereItem.details[0].data = "Reboot the console dirrectly back into Atmosphere, requires Atmosphere 0.8.3+. After selecting this option the console will crash, press volume up after the crash screen shows to finish the restart. Do not use this with exFAT, it may cause corruption!";
	menu.addMenuItem(3, rebootAtmosphereItem);
	menuItem rebootRCMItem;
	rebootRCMItem.name = "Reboot To RCM";
	rebootRCMItem.status = false;
	rebootRCMItem.details.push_back(menuDetail());
	rebootRCMItem.details[0].prefix = "Discription:\n";
	rebootRCMItem.details[0].data = "Reboot the console dirrectly into RCM mode, requires Atmosphere 0.8.1+. Do not use this with exFAT, it may cause corruption!";
	menu.addMenuItem(3, rebootRCMItem);
	menuItem updateItem;
	updateItem.name = "Update NSWreleases.xml";
	updateItem.status = false;
	updateItem.details.push_back(menuDetail());
	updateItem.details[0].prefix = "Discription:\n";
	updateItem.details[0].data = "This tool comes bundled with a NSWreleases.xml winthin it's romfs. This option will download a updated one to the root of the SD card. Restart the tool afterwards to use the new file.";
	menu.addMenuItem(3, updateItem);
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
				switch (menu.getMenuSelected()) {
				case 0:
					menu.toggleSelected();
					menu.drawMenu();
					rebootToPayload("sdmc:/atmosphere/reboot_payload.bin");
					break;
				case 1:
					menu.toggleSelected();
					menu.drawMenu();
					rebootToRCM();
					break;
				case 2:
					menu.toggleSelected();
					menu.drawMenu();
					lfs.updateLFSDatabase();
					menu.toggleSelected();
					menu.drawMenu();
					break;
				}
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
