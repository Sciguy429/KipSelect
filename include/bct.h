#pragma once

#include <string>
#include <vector>

#include "menu.h"

typedef struct {
	std::string name;
	std::string target;
	std::string description;
	bool enabled;
} bctItem;

class BCT {
public:
	void scanBCT();
	void setBCTItemEnabled(unsigned int bctId, bool enabled);
	bool getBCTItemEnabled(unsigned int bctId);
	unsigned int getBCTItemCount();
	menuItem getBCTMenuItem(unsigned int bctId);
private:
	std::vector<bctItem> bctItems;
	std::string bctNames[3] = {"Debug Mode", "Debug Mode User", "No Gamecard"};
	std::string bctTargets[3] = {"debugmode = ", "debugmode_user = ", "nogc = "};
};