#include <string>
#include <sstream>
#include <vector>

#include "menu.h"

void MENU::init() {
	//LOAD ASSETS
	mainFont = gfxCreateFontFromTTF("romfs:/font/sans.ttf");
	backroundTex = gfxCreateTextureFromPNG("romfs:/png/backround.png");
	menuBar = gfxCreateTextureFromPNG("romfs:/png/menuBar.png");
	menuBarSelected = gfxCreateTextureFromPNG("romfs:/png/menuBarSelected.png");
	//END LOAD ASSETS
	std::ostringstream ss;
	ss << "Version " << VERSION_MAJOR << '.' << VERSION_MINOR << '.' << VERSION_MICRO;
	gfxDrawText(backroundTex, ss.str().c_str(), mainFont, 140, 80, 15, RGBA8(255, 255, 255, 0));
}

void MENU::addTab(std::string tabName) {
	menuTab.push_back(tabName);
}

void MENU::addOpt(int tabId, std::string optName) {
	menuOpt.push_back(optName);
}

void MENU::resetMenu() {
	//stub
}

void MENU::drawMenu() {
	gfxBlit(frameBuffer, backroundTex, 0, 0, 0);
	for (unsigned int i = 0; i < menuOpt.size(); i++) {
		unsigned int drawY = 178 + (i * 64);
		if (i == 1) {
			gfxBlit(frameBuffer, menuBarSelected, 0, drawY, 0);
		}
		else {
			gfxBlit(frameBuffer, menuBar, 0, drawY, 0);
		}
		gfxDrawText(frameBuffer, menuOpt[i].c_str(), mainFont, 16, drawY + 16, 32, RGBA8(255, 255, 255, 0));
	}
}

void MENU::destroyAssets() {
	gfxDestroyFont(mainFont);
	gfxDestroyTexture(backroundTex);
	gfxDestroyTexture(menuBar);
	gfxDestroyTexture(menuBarSelected);
}
