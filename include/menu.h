#pragma once

#include <switch.h>
#include <string>
#include <vector>

#include "gfx.h"

typedef struct {
	std::string name;
	std::string md5;
	std::string version;
	std::string description;
	std::string data;
	bool enabled;
} menuItem;

class MENU {
public:
	void init();
	void setTabSelected(unsigned int tabId);
	unsigned int getTabSelected();
	void setMenuSelected(unsigned int menuId);
	unsigned int getMenuSelected();
	unsigned int getMenuSize();
	void addMenuItem(unsigned int tab, std::string name, std::string md5, std::string version, std::string description, std::string data, bool enabled);
	void resetMenu();
	void drawMenu();
	void destroyAssets();
private:
	unsigned int tabSelected;
	unsigned int menuSelected;
	std::vector<menuItem> kips;
	std::vector<menuItem> bct;
	std::vector<menuItem> layeredFS;
	std::vector<menuItem> options;
	//ASSETS
	texture *background;
	font *mainFont;
	texture *menuBar;
	texture *menuBarSelected;
	texture *checkmark;
	texture *questionmark;
	texture *tabKips;
	texture *tabKipsSelected;
	texture *tabBCT;
	texture *tabBCTSelected;
	texture *tabLayeredFS;
	texture *tabLayeredFSSelected;
	texture *tabOptions;
	texture *tabOptionsSelected;
};