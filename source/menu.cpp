#include <string>
#include <sstream>
#include <vector>

#include "menu.h"

void MENU::init() {
	mainFont = gfxCreateFontFromTTF("romfs:/font/sans.ttf");
	backroundTex = gfxCreateTextureFromPNG("romfs:/png/backround.png");
	std::ostringstream ss;
	ss << "Version " << VERSION_MAJOR << '.' << VERSION_MINOR << '.' << VERSION_MICRO;
	gfxDrawText(backroundTex, ss.str().c_str(), mainFont, 140, 80, 15, RGBA8(255, 255, 255, 0));

	gfxBlit(frameBuffer, backroundTex, 0, 0, 0);
}

void MENU::addTab(std::string tabName) {
	//stub
}

void MENU::addOpt(int tabId, std::string optName) {
	//stub
}

void MENU::resetMenu() {
	//stub
}

void MENU::handleInput(uint64_t kDown) {
	//stub
}

void MENU::destroyAssets() {
	gfxDestroyFont(mainFont);
	gfxDestroyTexture(backroundTex);
}
