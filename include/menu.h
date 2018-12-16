#pragma once

#include <switch.h>
#include <string>
#include <vector>

#include "gfx.h"

class MENU {
public:
	void init();
	void addTab(std::string tabName);
	void addOpt(int tabId, std::string optName);
	void resetMenu();
	void handleInput(uint64_t kDown);
	void destroyAssets();
private:
	texture *backroundTex;
	font *mainFont;
	std::vector<std::vector<std::string>> menuMatrix;
};