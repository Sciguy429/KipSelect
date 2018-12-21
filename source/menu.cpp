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
	detailEnabled = gfxCreateTexture(243, 59);
	gfxBlit(detailEnabled, purpleBox, 0, 0);
	gfxDrawText(detailEnabled, "Enabled", mainFont, 8, 8, 30, RGBA8(255, 255, 255, 0));
	//-Detail Disabled
	detailDisabled = gfxCreateTexture(243, 59);
	gfxBlit(detailDisabled, grayBox, 0, 0);
	gfxDrawText(detailDisabled, "Disabled", mainFont, 8, 8, 30, RGBA8(50, 50, 50, 0));
	//-Detail Loaded
	detailLoaded = gfxCreateTexture(243, 59);
	gfxBlit(detailLoaded, purpleBox, 0, 0);
	gfxDrawText(detailLoaded, "Loaded", mainFont, 8, 8, 30, RGBA8(255, 255, 255, 0));
	//-Detail Unloaded
	detailUnloaded = gfxCreateTexture(243, 59);
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
	menuSelected = 0;
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

void MENU::toggleSelected() {
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
		(*mnu)[menuSelected].status = !(*mnu)[menuSelected].status;
	}
}

void MENU::addMenuItem(unsigned int tab, menuItem itm) {
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
	mnu->push_back(itm);
}

void MENU::resetMenu() {
	tabSelected = 0;
	menuSelected = 0;
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
		unsigned int offset;
		unsigned int offsetLimit;
		if ((int)(menuSelected - 7) > 0) {
			if ((menuSelected - 7) < mnu->size()) {
				offset = menuSelected - 7;
			}
			else {
				offset = mnu->size() - 8;
			}
		}
		else {
			offset = 0;
		}
		if (mnu->size() - offset < 8) {
			offsetLimit = mnu->size();
		}
		else {
			offsetLimit = offset + 8;
		}
		for (unsigned int i = offset; i < offsetLimit; i++) {
			unsigned int drawY = 178 + ((i - offset) * 64);
			if (i == menuSelected) {
				gfxBlit(frameBuffer, menuBarSelected, 0, drawY);
			}
			else {
				gfxBlit(frameBuffer, menuBar, 0, drawY);
			}
			if ((*mnu)[i].status) {
				gfxBlit(frameBuffer, checkmark, 825, drawY + 16);
			}
			gfxDrawText(frameBuffer, (*mnu)[i].name.c_str(), mainFont, 16, drawY + 16, 32, RGBA8(255, 255, 255, 0));
		}
		gfxDrawText(frameBuffer, (*mnu)[menuSelected].name.c_str(), mainFont, 905, 178, 18, RGBA8(255, 255, 255, 0));
		for (unsigned int i = 0; i < (*mnu)[menuSelected].details.size(); i++) {
			unsigned int curX = i * 18 + 202;
			std::ostringstream ss;
			ss << (*mnu)[menuSelected].details[i].prefix << (*mnu)[menuSelected].details[i].data << (*mnu)[menuSelected].details[i].suffix;
			gfxDrawText(frameBuffer, ss.str().c_str(), mainFont, 905, curX, 12, RGBA8(255, 255, 255, 0));
		}
		if ((*mnu)[menuSelected].status) {
			gfxBlit(frameBuffer, detailEnabled, 972, 652);
		}
		else {
			gfxBlit(frameBuffer, detailDisabled, 972, 652);
		}
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