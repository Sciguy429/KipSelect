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
	ss << "Version " << VERSION_MAJOR << '.' << VERSION_MINOR << '.' << VERSION_MICRO;
	gfxDrawText(background, ss.str().c_str(), versionFont, 192, 135, 18, RGBA8(255, 255, 255, 0));
	gfxDestroyFont(versionFont);
}

void MENU::setTabSelected(unsigned int tabId) {
	tabSelected = tabId;
}

void MENU::setOptSelected(unsigned int menuId) {
	menuSelected = menuId;
}

void MENU::addTab(std::string tabName) {
	unsigned int size = menuTabs.size();
	menuTabs.push_back(menuTab());
	menuTabs[size].id = size;
	menuTabs[size].name = tabName;
}

void MENU::addOpt(int tabId, std::string optName) {
	unsigned int size = menuTabs[tabId].opt.size();
	menuTabs[tabId].opt.push_back(menuOpt());
	menuTabs[tabId].opt[size].id = size;
	menuTabs[tabId].opt[size].name = optName;
}

void MENU::resetMenu() {
	menuTabs.clear();
}

void MENU::drawMenu() {
	gfxBlit(frameBuffer, background, 0, 0);
	gfxBlit(frameBuffer, tabSelected == 0 ? tabKipsSelected : tabKips, 560, 118);
	gfxBlit(frameBuffer, tabSelected == 1 ? tabBCTSelected : tabBCT, 683, 118);
	gfxBlit(frameBuffer, tabSelected == 2 ? tabLayeredFSSelected : tabLayeredFS, 843, 118);
	gfxBlit(frameBuffer, tabSelected == 3 ? tabOptionsSelected : tabOptions, 1088, 118);

	/*
	if (!menuTabs.empty()) {
		for (unsigned int i = 0; i < menuTabs[menuTabSelected].opt.size(); i++) {
			unsigned int drawY = 178 + (i * 64);
			if (i == menuOptSelected) {
				gfxBlit(frameBuffer, menuBarSelected, 0, drawY);
			}
			else {
				gfxBlit(frameBuffer, menuBar, 0, drawY);
			}
			gfxDrawText(frameBuffer, menuTabs[0].opt[i].name.c_str(), mainFont, 16, drawY + 16, 32, RGBA8(255, 255, 255, 0));
		}
		gfxBlit(frameBuffer, tabKips, 400, 400);
	}
	*/
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
