#include <string>
#include <sstream>
#include <vector>

#include "menu.h"

void MENU::init() {
	menuTabSelected = 0;
	menuOptSelected = 0;
	//LOAD ASSETS
	mainFont = gfxCreateFontFromTTF("romfs:/font/bahnschrift.ttf");
	font *versionFont = gfxCreateFontFromTTF("romfs:/font/tt0288m_.ttf");
	backroundTex = gfxCreateTextureFromPNG("romfs:/png/background.png");
	menuBar = gfxCreateTextureFromPNG("romfs:/png/menu_bar.png");
	menuBarSelected = gfxCreateTextureFromPNG("romfs:/png/menu_bar_selected.png");
	//END LOAD ASSETS
	std::ostringstream ss;
	ss << "Version " << VERSION_MAJOR << '.' << VERSION_MINOR << '.' << VERSION_MICRO;
	gfxDrawText(backroundTex, ss.str().c_str(), versionFont, 1170, 700, 16, RGBA8(255, 255, 255, 0));
	gfxDestroyFont(versionFont);
}

void MENU::setTabSelected(unsigned int tabId) {
	menuTabSelected = tabId;
}

void MENU::setOptSelected(unsigned int optId) {
	menuOptSelected = optId;
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
	if (!menuTabs.empty()) {
		gfxBlit(frameBuffer, backroundTex, 0, 0, 0);
		for (unsigned int i = 0; i < menuTabs[menuTabSelected].opt.size(); i++) {
			unsigned int drawY = 178 + (i * 64);
			if (i == menuOptSelected) {
				gfxBlit(frameBuffer, menuBarSelected, 0, drawY, 0);
			}
			else {
				gfxBlit(frameBuffer, menuBar, 0, drawY, 0);
			}
			gfxDrawText(frameBuffer, menuTabs[0].opt[i].name.c_str(), mainFont, 16, drawY + 16, 32, RGBA8(255, 255, 255, 0));
		}
	}
}

void MENU::destroyAssets() {
	gfxDestroyFont(mainFont);
	gfxDestroyTexture(backroundTex);
	gfxDestroyTexture(menuBar);
	gfxDestroyTexture(menuBarSelected);
}
