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
	void drawMenu();
	void destroyAssets();
private:
	texture *backroundTex;
	font *mainFont;
	texture *menuBar;
	texture *menuBarSelected;
	std::vector<std::string> menuTab;
	std::vector<std::string> menuOpt;
};