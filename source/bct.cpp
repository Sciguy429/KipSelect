#include <fstream>
#include <string>

#include "bct.h"
#include "console.h"

using namespace std;

void bct::readBCT() {
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

void bct::setBCT(int bctId, bool enabled) {
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
			//printError(4, "");
			log("Couln't Open /atmosphere/BCT.ini", LOG_LEVEL_ERROR);
		}
	}
	else {
		//printError(5, bctName[bctId]);
		log("Couldnt Find Value In /atmosphere/BCT.ini", LOG_LEVEL_ERROR);
	}
}