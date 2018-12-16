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
	void setOptSelected(unsigned int menuId);
	void addTab(std::string tabName);
	void addOpt(int tabId, std::string optName);
	void resetMenu();
	void drawMenu();
	void destroyAssets();
private:
	unsigned int tabSelected;
	unsigned int menuSelected;
	std::vector<menuTab> menuTabs;
	//ASSETS
	texture *background;
	font *mainFont;
	texture *menuBar;
	texture *menuBarSelected;
	texture *tabKips;
	texture *tabKipsSelected;
	texture *tabBCT;
	texture *tabBCTSelected;
	texture *tabLayeredFS;
	texture *tabLayeredFSSelected;
	texture *tabOptions;
	texture *tabOptionsSelected;
};