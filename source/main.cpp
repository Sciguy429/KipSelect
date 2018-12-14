#include <switch.h>
#include <string>

#include "console.h"
#include "kip.h"
#include "bct.h"

using namespace std;

bool run = true;
u64 kDown;
/*
void updateInputs() {
	hidScanInput();
	kDown = hidKeysDown(CONTROLLER_P1_AUTO);
	if (kDown & KEY_PLUS) run = false;
}

void printError(int errorCode, string extra) {
	printf(CONSOLE_ESC(2J) CONSOLE_RED "An Error Has Occured! (Error Code: %d) Press + To Exit Back To HB-Menu\n\n", errorCode);
	switch (errorCode) {
	case 0:
		printf("Unable To Make Dirrectory: %s", extra.c_str());
		break;
	case 1:
		printf("No Kips Found!\nDid You Install Any?");
		break;
	case 2:
		printf("More Than %d Kips Found!", KIP_LIST_LENGTH);
		break;
	case 3:
		printf("File Moved Failed!\nOffending Kip: '%s'\n\n\nThis Is Typicly Caused By A Kip Being Present In kips and kips_disabled\nAt The Same Time, Check These Folders First", extra.c_str());
		break;
	case 4:
		printf("Unabled To Open BCT.ini!");
		break;
	case 5:
		printf("Unabled To Find Value In BCT.ini!\nOffending Value: '%s'", extra.c_str());
		break;
	default:
		printf("UKNOWN ERROR\n(You're In DEEP Trouble If This Shows Up Lol :P)");
		break;
	}
	while (run) {
		consoleUpdate(NULL);
		updateInputs();
	}
}

void printWarning(int warningCode, string extra) {
	printf(CONSOLE_ESC(2J) CONSOLE_YELLOW "### WARNING (Warning Code: %d) ###\nPress + To Exit Back To HB-Menu, Press - To Continue\n\n", warningCode);
	switch (warningCode) {
	case 0:
		printf("REBOOTING VIA HOMEBREW WHILE USING EXFAT WILL CAUSE CORRUPTION!\n\n\nContinue at your own risk!");
		break;
	default:
		printf("UKNOWN WARNING\n\n\nProceed With Caution!");
		break;
	}
	while (run) {
		consoleUpdate(NULL);
		updateInputs();
		if (kDown & KEY_MINUS) {
			return;
		}
	}
}
*/
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
