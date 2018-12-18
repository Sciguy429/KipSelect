#include <sstream>

#include "menu.h"

void MENU::init() {
	tabSelected = 0;
	menuSelected = 0;
	//LOAD ASSETS
	//-Fonts
	mainFont = gfxCreateFontFromTTF("romfs:/font/bahnschrift.ttf");
	font *versionFont = gfxCreateFontFromTTF("romfs:/font/tt0288m_.ttf");
	//-Textures
	background = gfxCreateTextureFromPNG("romfs:/png/background.png");
	menuBar = gfxCreateTextureFromPNG("romfs:/png/menu/menu_bar.png");
	menuBarSelected = gfxCreateTextureFromPNG("romfs:/png/menu/menu_bar_selected.png");
	checkmark = gfxCreateTextureFromPNG("romfs:/png/menu/checkmark.png");
	questionmark = gfxCreateTextureFromPNG("romfs:/png/menu/questionmark.png");
	tabKips = gfxCreateTextureFromPNG("romfs:/png/tab/tab_kips.png");
	tabKipsSelected = gfxCreateTextureFromPNG("romfs:/png/tab/tab_kips_selected.png");
	tabBCT = gfxCreateTextureFromPNG("romfs:/png/tab/tab_bct.png");
	tabBCTSelected = gfxCreateTextureFromPNG("romfs:/png/tab/tab_bct_selected.png");
	tabLayeredFS = gfxCreateTextureFromPNG("romfs:/png/tab/tab_layeredfs.png");
	tabLayeredFSSelected = gfxCreateTextureFromPNG("romfs:/png/tab/tab_layeredfs_selected.png");
	tabOptions = gfxCreateTextureFromPNG("romfs:/png/tab/tab_options.png");
	tabOptionsSelected = gfxCreateTextureFromPNG("romfs:/png/tab/tab_options_selected.png");
	texture *purpleBox = gfxCreateTextureFromPNG("romfs:/png/detail/detail_purple.png");
	texture *grayBox = gfxCreateTextureFromPNG("romfs:/png/detail/detail_gray.png");
	//END LOAD ASSETS
	//BUILD ASSETS
	//-Detail Enabled
	detailEnabled = gfxCreateTexture(236, 52);
	gfxFill(detailEnabled, RGBA8(70, 70, 70, 0));
	gfxBlit(detailEnabled, purpleBox, 0, 0);
	gfxDrawText(detailEnabled, "Enabled", mainFont, 8, 8, 30, RGBA8(255, 255, 255, 0));
	//-Detail Disabled
	detailDisabled = gfxCreateTexture(236, 52);
	gfxFill(detailDisabled, RGBA8(70, 70, 70, 0));
	gfxBlit(detailDisabled, grayBox, 0, 0);
	gfxDrawText(detailDisabled, "Disabled", mainFont, 8, 8, 30, RGBA8(50, 50, 50, 0));
	//-Detail Loaded
	detailLoaded = gfxCreateTexture(236, 52);
	gfxFill(detailLoaded, RGBA8(70, 70, 70, 0));
	gfxBlit(detailLoaded, purpleBox, 0, 0);
	gfxDrawText(detailLoaded, "Loaded", mainFont, 8, 8, 30, RGBA8(255, 255, 255, 0));
	//-Detail Unloaded
	detailUnloaded = gfxCreateTexture(236, 52);
	gfxFill(detailUnloaded, RGBA8(70, 70, 70, 0));
	gfxBlit(detailUnloaded, grayBox, 0, 0);
	gfxDrawText(detailUnloaded, "Unloaded", mainFont, 8, 8, 30, RGBA8(50, 50, 50, 0));
	//-Destroy Base Assets
	gfxDestroyTexture(purpleBox);
	gfxDestroyTexture(grayBox);
	//-Add Version To Backround
	std::ostringstream version;
	version << 'v' << VERSION_MAJOR << '.' << VERSION_MINOR << '.' << VERSION_MICRO;
	gfxDrawText(background, version.str().c_str(), versionFont, 380, 59, 18, RGBA8(194, 17, 170, 0));
	gfxDestroyFont(versionFont);
	//END BUILD
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

void MENU::addMenuItem(unsigned int tab, std::string name, std::vector<menuDetail> details, int status) {
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
	(*mnu)[pos].details = details;
	(*mnu)[pos].status = status;
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
	std::vector<menuItem> *mnu = new std::vector<menuItem>;
	switch (tabSelected) {
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
	if (mnu->size() > 0) {
		for (unsigned int i = 0; i < mnu->size(); i++) {
			unsigned int drawY = 178 + (i * 64);
			if (i == menuSelected) {
				gfxBlit(frameBuffer, menuBarSelected, 0, drawY);
			}
			else {
				gfxBlit(frameBuffer, menuBar, 0, drawY);
			}
			switch ((*mnu)[i].status) {
			case (1):
				gfxBlit(frameBuffer, checkmark, 825, drawY + 16);
				break;
			case (2):
				gfxBlit(frameBuffer, questionmark, 825, drawY + 16);
				break;
			default:
				break;
			}
			gfxDrawText(frameBuffer, (*mnu)[i].name.c_str(), mainFont, 16, drawY + 16, 32, RGBA8(255, 255, 255, 0));
			gfxDrawText(frameBuffer, (*mnu)[menuSelected].name.c_str(), mainFont, 905, 178, 18, RGBA8(255, 255, 255, 0));
			for (unsigned int d = 0; d < (*mnu)[menuSelected].details.size(); d++) {
				unsigned int curX = d * 18 + 202;
				std::ostringstream ss;
				ss << (*mnu)[menuSelected].details[d].prefix << (*mnu)[menuSelected].details[d].data << (*mnu)[menuSelected].details[d].suffix;
				gfxDrawText(frameBuffer, ss.str().c_str(), mainFont, 905, curX, 12, RGBA8(255, 255, 255, 0));
			}
		}
		//gfxBlit(frameBuffer, detailUnloaded, 972, 652);
	}
}

void MENU::destroyAssets() {
	gfxDestroyFont(mainFont);
	gfxDestroyTexture(background);
	gfxDestroyTexture(menuBar);
	gfxDestroyTexture(menuBarSelected);
	gfxDestroyTexture(checkmark);
	gfxDestroyTexture(questionmark);
	gfxDestroyTexture(tabKips);
	gfxDestroyTexture(tabKipsSelected);
	gfxDestroyTexture(tabBCT);
	gfxDestroyTexture(tabBCTSelected);
	gfxDestroyTexture(tabLayeredFS);
	gfxDestroyTexture(tabLayeredFSSelected);
	gfxDestroyTexture(tabOptions);
	gfxDestroyTexture(tabOptionsSelected);
	gfxDestroyTexture(detailEnabled);
	gfxDestroyTexture(detailDisabled);
	gfxDestroyTexture(detailLoaded);
	gfxDestroyTexture(detailUnloaded);
}