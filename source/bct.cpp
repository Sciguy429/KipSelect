#include <fstream>

#include "bct.h"

void BCT::scanBCT() {
	std::ifstream bctIfStream("/atmosphere/BCT.ini");
	std::string bctString((std::istreambuf_iterator<char>(bctIfStream)), (std::istreambuf_iterator<char>()));
	bctIfStream.close();
	for (unsigned int i = 0; i < (sizeof(bctTargets) / sizeof(*bctTargets)); i++) {
		size_t debugModeLocation = bctString.find(bctTargets[i].c_str(), 0) + bctTargets[i].length();
		unsigned int pos = bctItems.size();
		bctItems.push_back(bctItem());
		bctItems[pos].name = bctNames[i];
		if (bctString[debugModeLocation] - 48 == 1) {
			bctItems[pos].enabled = true;
		}
		else {
			bctItems[pos].enabled = false;
		}
	}
}
/*
void BCT::setBCT(int bctId, bool enabled) {
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
			//TODO: Throw a proper error here (error.h/error.cpp)
		}
	}
	else {
		//TODO: Throw a proper error here (error.h/error.cpp)
	}
}

int BCT::getBCTCount() {
	return BCT_LIST_LENGTH;
}

string BCT::getBCTName(int bctId) {
	return bctName[bctId];
}

bool BCT::getBCTValue(int bctId) {
	return bctValue[bctId];
}
*/