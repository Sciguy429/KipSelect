#pragma once

#include <string>
#include <vector>

#include "menu.h"

typedef struct {
	std::string name;
	std::string description;
	bool enabled;
} bctItem;

class BCT {
public:
	void scanBCT();
	//void setBCTItemEnabled(unsigned int bctId, bool enabled);
	unsigned int getBCTItemCount();
	menuItem getBCTMenuItem(unsigned int bctId);
private:
	std::vector<bctItem> bctItems;
	std::string bctTargets[2] = {"debugmode", "debugmode_user"};
};