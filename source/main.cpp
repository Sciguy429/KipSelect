#include <switch.h>

#include "screen/gfx.h"
#include "error.h"
#include "cfw/kip.h"
#include "cfw/bct.h"
#include "cfw/lfs.h"
#include "utils/reboot.h"

#include "screen/scene.h"

#include "screen/thread/render.h"

int main(int argc, char **argv) {
	u32 mainThreadCore = svcGetCurrentProcessorNumber();
	u32 renderThreadCore = mainThreadCore + 1;
	if (renderThreadCore > 3) {
		renderThreadCore = 0;
	}
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
	//TEST
	SCENE testS("Nope");
	TEXT *testText = (TEXT*)testS.getObjectVector("yes");
	printf("MAIN -- 2 -- %s\n", testText->getText().c_str());
	//
	renderThreadControlVector rTCV;
	rTCV.runThread = true;
	Thread testThread;
	threadCreate(&testThread, &renderThread, &rTCV, 0x19000, 0x2C, renderThreadCore);
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
			rTCV.runThread = false;
			threadWaitForExit(&testThread);
		}
		else if (kDown & KEY_UP) {
			//U
		}
		else if (kDown & KEY_DOWN) {
			//D
		}
		else if (kDown & KEY_A) {
			//A
			threadStart(&testThread);
		}
	}
	threadClose(&testThread);
	errorDestroyAssets();
	gfxCleanUp();
	romfsExit();
	socketExit();
	return 0;
}