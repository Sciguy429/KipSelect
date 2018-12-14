#include <switch.h>
#include <string>

#include "console.h"
#include "kip.h"
#include "bct.h"

using namespace std;

bool run = true;
u64 kDown;

int main(int argc, char **argv)
{
	KIP kip;
	BCT bct;
	consoleInit(NULL);
	initLocalConsole();
	log("Scanning For Kips", LOG_LEVEL_INFO);
	kip.scanForKip();
	log(SSTR("Found " << kip.getKipCount() << " Kips"), LOG_LEVEL_INFO);
	log("Scanning For BCT Values", LOG_LEVEL_INFO);
	bct.readBCT();
	log(SSTR("Found " << bct.getBCTCount() << " BCT Values"), LOG_LEVEL_INFO);
	while (appletMainLoop) {
		hidScanInput();
		u32 kdown = hidKeysDown(CONTROLLER_P1_AUTO);
		if (kdown & KEY_PLUS) {
			break;
		}
		consoleUpdate(NULL);
	}
	consoleExit(NULL);
	return 0;
}
