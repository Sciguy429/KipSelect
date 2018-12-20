#include <fstream>

#include "bct.h"

void BCT::scanBCT() {
	std::ifstream bctIfStream("/atmosphere/BCT.ini");
	std::string bctString((std::istreambuf_iterator<char>(bctIfStream)), (std::istreambuf_iterator<char>()));
	bctIfStream.close();
	for (unsigned int i = 0; i < (sizeof(bctTargets) / sizeof(*bctTargets)); i++) {
		size_t debugModeLocation = bctString.find(bctTargets[i].c_str(), 0) + bctTargets[i].length();
		if (debugModeLocation != std::string::npos) {
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
}

void BCT::setBCTItemEnabled(unsigned int bctId, bool enabled) {
	std::ifstream bctIfStream("/atmosphere/BCT.ini");
	std::string bctString((std::istreambuf_iterator<char>(bctIfStream)), (std::istreambuf_iterator<char>()));
	bctIfStream.close();
	size_t location = bctString.find(bctTargets[bctId].c_str(), 0);
	if (location != std::string::npos) {
		bctString[location] = 48 + enabled;
		std::ofstream bctOfStream("/atmosphere/BCT.ini");
		if (bctOfStream.is_open()) {
			bctOfStream << bctString;
			bctOfStream.close();
		}
		else {
			//TODO: Throw a proper error here (error.h/error.cpp)
		}
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