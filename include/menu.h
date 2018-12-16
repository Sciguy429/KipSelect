#pragma once

#include <switch.h>
#include <string>
#include <vector>

#include "gfx.h"

typedef struct {
	unsigned int id;
	std::string name;
	std::string version;
	std::string description;
	std::string data;
	bool enabled;
} menuOpt;

typedef struct {
	unsigned int id;
	std::string name;
	std::vector<menuOpt> opt;
} menuTab;

class MENU {
public:
	void init();
	void setTabSelected(unsigned int tabId);
	void setOptSelected(unsigned int optId);
	void addTab(std::string tabName);
	void addOpt(int tabId, std::string optName);
	void resetMenu();
	void drawMenu();
	void destroyAssets();
private:
	unsigned int menuTabSelected;
	unsigned int menuOptSelected;
	texture *background;
	font *mainFont;
	texture *menuBar;
	texture *menuBarSelected;
	std::vector<menuTab> menuTabs;
};