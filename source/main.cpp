#include <switch.h>

#include "screen/gfx.h"
#include "error.h"
#include "cfw/kip.h"
#include "cfw/bct.h"
#include "cfw/lfs.h"
#include "utils/reboot.h"

int main(int argc, char **argv) {
	KIP kip;
	BCT bct;
	LFS lfs;
	socketInitializeDefault();
	nxlinkStdio();
	romfsInit();
	gfxInit(1280, 720);
	errorLoadAssets();
	lfs.parseLFSDatabase();
	lfs.parseSysDatabase();
	kip.scanKIP();
	bct.scanBCT();
	lfs.scanLFS();
	//INIT NEW MENU SCENE HERE
	while (appletMainLoop() && !isErrorThrown()) {
		hidScanInput();
		u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);
		if (kDown & KEY_PLUS) {
			break;
		}
		else if (kDown & KEY_L) {
			//L
		}
		else if (kDown & KEY_R) {
			//R
		}
		else if (kDown & KEY_UP) {
			//U
		}
		else if (kDown & KEY_DOWN) {
			//D
		}
		else if (kDown & KEY_A) {
			//A
		}
	}
	errorDestroyAssets();
	gfxCleanUp();
	romfsExit();
	socketExit();
	return 0;
}