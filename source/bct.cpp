#include <fstream>

#include "bct.h"
#include "error.h"

void BCT::scanBCT() {
	bctItems.clear();
	std::ifstream bctIfStream("/atmosphere/BCT.ini");
	std::string bctString((std::istreambuf_iterator<char>(bctIfStream)), (std::istreambuf_iterator<char>()));
	bctIfStream.close();
	for (unsigned int i = 0; i < (sizeof(bctTargets) / sizeof(*bctTargets)); i++) {
		size_t debugModeLocation = bctString.find(bctTargets[i].c_str(), 0);
		if (debugModeLocation != std::string::npos) {
			unsigned int pos = bctItems.size();
			bctItems.push_back(bctItem());
			bctItems[pos].name = bctNames[i];
			bctItems[pos].target = bctTargets[i];
			if (bctString[debugModeLocation + bctTargets[i].length()] - 48 == 1) {
				bctItems[pos].enabled = true;
			}
			else {
				bctItems[pos].enabled = false;
			}
		}
	}
}

void BCT::setBCTItemEnabled(unsigned int bctId, bool enabled) {
	bctItems[bctId].enabled = enabled;
	std::ifstream bctIfStream("/atmosphere/BCT.ini");
	std::string bctString((std::istreambuf_iterator<char>(bctIfStream)), (std::istreambuf_iterator<char>()));
	bctIfStream.close();
	size_t location = bctString.find(bctTargets[bctId].c_str(), 0);
	if (location != std::string::npos) {
		bctString[location + bctTargets[bctId].length()] = 48 + enabled;
		std::ofstream bctOfStream("/atmosphere/BCT.ini");
		if (bctOfStream.is_open()) {
			bctOfStream << bctString;
			bctOfStream.close();
		}
		else {
			errorThrow(2);
		}
	}
	else {
		errorThrow(3);
	}
}

bool BCT::getBCTItemEnabled(unsigned int bctId) {
	return bctItems[bctId].enabled;
}

unsigned int BCT::getBCTItemCount() {
	return bctItems.size();
}

menuItem BCT::getBCTMenuItem(unsigned int bctId) {
	menuItem mnu;
	mnu.name = bctItems[bctId].name;
	mnu.details.push_back(menuDetail());
	mnu.details[0].prefix = "Target: '";
	mnu.details[0].data = bctItems[bctId].target;
	mnu.details[0].suffix = "'";
	mnu.details.push_back(menuDetail());
	mnu.details[1].prefix = "Discription:\n";
	mnu.details[1].data = "This is a test of a discription";
	return mnu;
}