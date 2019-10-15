#include <switch.h>

#include "screen/gfx.h"
#include "screen/error.h"
#include "screen/menu.h"
#include "cfw/kip.h"
#include "cfw/bct.h"
#include "cfw/lfs.h"
#include "utils/reboot.h"

int main(int argc, char** argv) {
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
	lfs.parseUsrDatabase();
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
	rebootAtmosphereItem.details[0].prefix = "Target: ";
	rebootAtmosphereItem.details[0].data = "'sdmc:/atmospshere/reboot_payload.bin'";
	rebootAtmosphereItem.details.push_back(menuDetail());
	rebootAtmosphereItem.details[1].prefix = "Discription: ";
	rebootAtmosphereItem.details[1].data = "Reboot the console dirrectly back into Atmosphere, requires Atmosphere 0.8.3+. After selecting this option the console will crash, press volume up after the crash screen shows to finish the restart. Do not use this with exFAT, it may cause corruption!";
	menu.addMenuItem(3, rebootAtmosphereItem);
	menuItem rebootRCMItem;
	rebootRCMItem.name = "Reboot To RCM";
	rebootRCMItem.status = false;
	rebootRCMItem.details.push_back(menuDetail());
	rebootRCMItem.details[0].prefix = "Discription: ";
	rebootRCMItem.details[0].data = "Reboot the console dirrectly into RCM mode, requires Atmosphere 0.8.1+. Do not use this with exFAT, it may cause corruption!";
	menu.addMenuItem(3, rebootRCMItem);
	menuItem nswUpdateItem;
	nswUpdateItem.name = "Update NSWreleases.xml";
	nswUpdateItem.status = false;
	nswUpdateItem.details.push_back(menuDetail());
	nswUpdateItem.details[0].prefix = "Target: ";
	nswUpdateItem.details[0].data = "'sdmc:/NSWreleases.xml'";
	nswUpdateItem.details.push_back(menuDetail());
	nswUpdateItem.details[1].prefix = "Discription: ";
	nswUpdateItem.details[1].data = "This tool comes bundled with a NSWreleases.xml winthin it's romfs. This option will download a updated one to the root of the SD card. Restart the tool afterwards to use the new file. If you get a error afterwards about a corrupted NSWreleases.xml, delete the file and try again.";
	menu.addMenuItem(3, nswUpdateItem);
	menu.drawMenu();
	while (appletMainLoop() && !isErrorThrown()) {
		hidScanInput();
		u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);
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