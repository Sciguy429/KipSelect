#include <switch.h>

#include "screen/gfx.h"
#include "error.h"
#include "cfw/kip.h"
#include "cfw/bct.h"
#include "cfw/lfs.h"
#include "utils/reboot.h"

#include "screen/scene.h"

void threadTest(void *) {
	printf("IM A THREAD!\n");
	gfxDrawRect(frameBufferTexture, 0, 0, 500, 500, RGBA8(255, 0, 0, 0), true);
	gfxDrawFrameBuffer();
}

int main(int argc, char **argv) {
	u32 currentCore = svcGetCurrentProcessorNumber();
	u32 renderThreadCore = currentCore + 1;
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
	printf("main() -- Running On Core: %d\n", currentCore);
	printf("renderThread() --- Running On Core: %d\n", renderThreadCore);
	errorLoadAssets();
	lfs.parseLFSDatabase();
	lfs.parseSysDatabase();
	kip.scanKIP();
	bct.scanBCT();
	lfs.scanLFS();
	//TEST
	Thread testThread;
	threadCreate(&testThread, &threadTest, NULL, 0x19000, 0x2C, renderThreadCore);
	//INIT NEW MENU SCENE HERE
	SCENE test("this dosen't matter yet...");
	TEXT *text = test.getTextObjectVector("nop");
	printf("VECTOR ID: %s\n", text->getId().c_str());
	printf("TEXT: %s\n", text->getText().c_str());
	//END TEST
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