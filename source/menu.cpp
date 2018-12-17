#include <string>
#include <sstream>
#include <vector>

#include "menu.h"

void MENU::init() {
	tabSelected = 0;
	menuSelected = 0;
	//LOAD ASSETS
	mainFont = gfxCreateFontFromTTF("romfs:/font/bahnschrift.ttf");
	font *versionFont = gfxCreateFontFromTTF("romfs:/font/tt0288m_.ttf");
	background = gfxCreateTextureFromPNG("romfs:/png/background.png");
	menuBar = gfxCreateTextureFromPNG("romfs:/png/menu/menu_bar.png");
	menuBarSelected = gfxCreateTextureFromPNG("romfs:/png/menu/menu_bar_selected.png");
	tabKips = gfxCreateTextureFromPNG("romfs:/png/tab/tab_kips.png");
	tabKipsSelected = gfxCreateTextureFromPNG("romfs:/png/tab/tab_kips_selected.png");
	tabBCT = gfxCreateTextureFromPNG("romfs:/png/tab/tab_bct.png");
	tabBCTSelected = gfxCreateTextureFromPNG("romfs:/png/tab/tab_bct_selected.png");
	tabLayeredFS = gfxCreateTextureFromPNG("romfs:/png/tab/tab_layeredfs.png");
	tabLayeredFSSelected = gfxCreateTextureFromPNG("romfs:/png/tab/tab_layeredfs_selected.png");
	tabOptions = gfxCreateTextureFromPNG("romfs:/png/tab/tab_options.png");
	tabOptionsSelected = gfxCreateTextureFromPNG("romfs:/png/tab/tab_options_selected.png");
	//END LOAD ASSETS
	std::ostringstream ss;
	ss << 'v' << VERSION_MAJOR << '.' << VERSION_MINOR << '.' << VERSION_MICRO;
	gfxDrawText(background, ss.str().c_str(), versionFont, 380, 60, 18, RGBA8(194, 17, 170, 0));
	gfxDestroyFont(versionFont);
}

void MENU::setTabSelected(unsigned int tabId) {
	tabSelected = tabId;
}

unsigned int MENU::getTabSelected() {
	return tabSelected;
}

void MENU::setMenuSelected(unsigned int menuId) {
	menuSelected = menuId;
}

unsigned int MENU::getMenuSelected() {
	return menuSelected;
}

unsigned int MENU::getMenuSize() {
	switch (tabSelected) {
	case 0:
		return kips.size();
	case 1:
		return bct.size();
	case 2:
		return layeredFS.size();
	case 3:
		return options.size();
	default:
		return 0;
	}
}

void MENU::addKipItem(std::string name, std::string version, std::string description, std::string data, bool enabled) {
	unsigned int pos = kips.size();
	kips.push_back(menuItem());
	kips[pos].name = name;
	kips[pos].version = version;
	kips[pos].description = description;
	kips[pos].data = data;
	kips[pos].enabled = enabled;
}

void MENU::addBCTItem(std::string name, std::string version, std::string description, std::string data, bool enabled) {
	unsigned int pos = bct.size();
	bct.push_back(menuItem());
	bct[pos].name = name;
	bct[pos].version = version;
	bct[pos].description = description;
	bct[pos].data = data;
	bct[pos].enabled = enabled;
}

void MENU::addLayeredFSItem(std::string name, std::string version, std::string description, std::string data, bool enabled) {
	unsigned int pos = layeredFS.size();
	layeredFS.push_back(menuItem());
	layeredFS[pos].name = name;
	layeredFS[pos].version = version;
	layeredFS[pos].description = description;
	layeredFS[pos].data = data;
	layeredFS[pos].enabled = enabled;
}

void MENU::addOptionsItem(std::string name, std::string version, std::string description, std::string data, bool enabled) {
	unsigned int pos = options.size();
	options.push_back(menuItem());
	options[pos].name = name;
	options[pos].version = version;
	options[pos].description = description;
	options[pos].data = data;
	options[pos].enabled = enabled;
}

void MENU::resetMenu() {
	kips.clear();
	bct.clear();
	layeredFS.clear();
	options.clear();
}

void MENU::drawMenu() {
	gfxBlit(frameBuffer, background, 0, 0);
	gfxBlit(frameBuffer, tabSelected == 0 ? tabKipsSelected : tabKips, 560, 118);
	gfxBlit(frameBuffer, tabSelected == 1 ? tabBCTSelected : tabBCT, 683, 118);
	gfxBlit(frameBuffer, tabSelected == 2 ? tabLayeredFSSelected : tabLayeredFS, 843, 118);
	gfxBlit(frameBuffer, tabSelected == 3 ? tabOptionsSelected : tabOptions, 1088, 118);
	std::vector<menuItem> mnu;
	switch (tabSelected) {
	case 0:
		mnu = kips;
		break;
	case 1:
		mnu = bct;
		break;
	case 2:
		mnu = layeredFS;
		break;
	case 3:
		mnu = options;
		break;
	}
	for (unsigned int i = 0; i < mnu.size(); i++) {
		unsigned int drawY = 178 + (i * 64);
		if (i == menuSelected) {
			gfxBlit(frameBuffer, menuBarSelected, 0, drawY);
		}
		else {
			gfxBlit(frameBuffer, menuBar, 0, drawY);
		}
		gfxDrawText(frameBuffer, mnu[i].name.c_str(), mainFont, 16, drawY + 16, 32, RGBA8(255, 255, 255, 0));
	}
}

void MENU::destroyAssets() {
	gfxDestroyFont(mainFont);
	gfxDestroyTexture(background);
	gfxDestroyTexture(menuBar);
	gfxDestroyTexture(menuBarSelected);
	gfxDestroyTexture(tabKips);
	gfxDestroyTexture(tabKipsSelected);
	gfxDestroyTexture(tabBCT);
	gfxDestroyTexture(tabBCTSelected);
	gfxDestroyTexture(tabLayeredFS);
	gfxDestroyTexture(tabLayeredFSSelected);
	gfxDestroyTexture(tabOptions);
	gfxDestroyTexture(tabOptionsSelected);
}
