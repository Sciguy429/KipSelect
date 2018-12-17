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
	checkmark = gfxCreateTextureFromPNG("romfs:/png/menu/checkmark.png");
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

void MENU::addMenuItem(unsigned int tab, std::string name, std::string version, std::string description, std::string data, bool enabled) {
	std::vector<menuItem> *mnu = new std::vector<menuItem>;
	switch (tab) {
	case 0:
		mnu = &kips;
		break;
	case 1:
		mnu = &bct;
		break;
	case 2:
		mnu = &layeredFS;
		break;
	case 3:
		mnu = &options;
		break;
	default:
		return;
	}
	unsigned int pos = mnu->size();
	mnu->push_back(menuItem());
	(*mnu)[pos].name = name;
	(*mnu)[pos].version = version;
	(*mnu)[pos].description = description;
	(*mnu)[pos].data = data;
	(*mnu)[pos].enabled = enabled;
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
		if (mnu[i].enabled) {
			gfxBlit(frameBuffer, checkmark, 825, drawY + 16);
		}
		gfxDrawText(frameBuffer, mnu[i].name.c_str(), mainFont, 16, drawY + 16, 32, RGBA8(255, 255, 255, 0));
	}
}

void MENU::destroyAssets() {
	gfxDestroyFont(mainFont);
	gfxDestroyTexture(background);
	gfxDestroyTexture(menuBar);
	gfxDestroyTexture(menuBarSelected);
	gfxDestroyTexture(checkmark);
	gfxDestroyTexture(tabKips);
	gfxDestroyTexture(tabKipsSelected);
	gfxDestroyTexture(tabBCT);
	gfxDestroyTexture(tabBCTSelected);
	gfxDestroyTexture(tabLayeredFS);
	gfxDestroyTexture(tabLayeredFSSelected);
	gfxDestroyTexture(tabOptions);
	gfxDestroyTexture(tabOptionsSelected);
}
