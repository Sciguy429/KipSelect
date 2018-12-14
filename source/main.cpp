#include <switch.h>
#include <string>
#include <fstream>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../include/console.h"

using namespace std;

#define BCT_LIST_LENGTH 2 //Amount of bct values currently editable


string bctName[BCT_LIST_LENGTH] = { "debugmode = ", "debugmode_user = " };
int bctValue[BCT_LIST_LENGTH] = { -1, -1 };
int menuSelected = 0;
int kipCount = 0;

bool run = true;
bool bctSelected = false;
u64 kDown;

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

void readBCT() {
	ifstream bctIfStream("/atmosphere/BCT.ini");
	string bctString((std::istreambuf_iterator<char>(bctIfStream)), (std::istreambuf_iterator<char>()));
	bctIfStream.close();
	size_t debugModeLocation = bctString.find("debugmode = ", 0) + 12;
	size_t debugModeUserLocation = bctString.find("debugmode_user = ", 0) + 17;
	if (debugModeLocation == string::npos) {
		bctValue[0] = -1;
	}
	else {
		bctValue[0] = bctString[debugModeLocation] - 48;
	}
	if (debugModeUserLocation == string::npos) {
		bctValue[1] = -1;
	}
	else {
		bctValue[1] = bctString[debugModeUserLocation] - 48;
	}
}

void setKip(int kipId, bool enabled) {
	string name = kipName[kipId];
	string start = "/atmosphere/";
	string end = "/atmosphere/";
	if (enabled) {
		start.append("kips_disabled/");
		end.append("kips/");
	}
	else {
		start.append("kips/");
		end.append("kips_disabled/");
	}
	start.append(name);
	end.append(name);
	if (rename(start.c_str(), end.c_str()) != 0) {
		printError(3, name);
	}
}

void setBCT(int bctId, bool enabled) {
	size_t location = string::npos;
	ifstream bctIfStream("/atmosphere/BCT.ini");
	string bctString((std::istreambuf_iterator<char>(bctIfStream)), (std::istreambuf_iterator<char>()));
	bctIfStream.close();
	switch (bctId) {
	case 0:
		location = bctString.find("debugmode = ", 0);
		if (location != string::npos) {
			location = location + 12;
		}
		break;
	case 1:
		location = bctString.find("debugmode_user = ", 0);
		if (location != string::npos) {
			location = location + 17;
		}
		break;
	default:
		break;
	}
	if (location != string::npos) {
		bctString[location] = 48 + enabled;
		ofstream bctOfStream("/atmosphere/BCT.ini");
		if (bctOfStream.is_open()) {
			bctOfStream << bctString;
			bctOfStream.close();
		}
		else {
			printError(4, "");
		}
	}
	else {
		printError(5, bctName[bctId]);
	}
}

int main(int argc, char **argv)
{
	consoleInit(NULL);
	initLocalConsole();

	log("info test", LOG_LEVEL_INFO);
	log("warning test", LOG_LEVEL_WARNING);
	log("error test", LOG_LEVEL_ERROR);

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
