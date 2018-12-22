#include <sstream>

#include "menu.h"

void MENU::registerAssets() {
	//REGISTER ASSETS
	//-Fonts
	mainFont = registerFont("romfs:/font/bahnschrift.ttf");
	versionFont = registerFont("romfs:/font/tt0288m_.ttf");
	//-Textures
	background = registerTexture("romfs:/png/background.png");
	menuBar = registerTexture("romfs:/png/menu/menu_bar.png");
	menuBarSelected = registerTexture("romfs:/png/menu/menu_bar_selected.png");
	checkmark = registerTexture("romfs:/png/menu/checkmark.png");
	questionmark = registerTexture("romfs:/png/menu/questionmark.png");
	menuScrollUp = registerTexture("romfs:/png/menu/menu_scroll_up.png");
	menuScrollDown = registerTexture("romfs:/png/menu/menu_scroll_down.png");
	tabKips = registerTexture("romfs:/png/tab/tab_kips.png");
	tabKipsSelected = registerTexture("romfs:/png/tab/tab_kips_selected.png");
	tabBCT = registerTexture("romfs:/png/tab/tab_bct.png");
	tabBCTSelected = registerTexture("romfs:/png/tab/tab_bct_selected.png");
	tabLayeredFS = registerTexture("romfs:/png/tab/tab_layeredfs.png");
	tabLayeredFSSelected = registerTexture("romfs:/png/tab/tab_layeredfs_selected.png");
	tabOptions = registerTexture("romfs:/png/tab/tab_options.png");
	tabOptionsSelected = registerTexture("romfs:/png/tab/tab_options_selected.png");
	detailEnabled = registerTexture("romfs:/png/detail/detail_enabled.png");
	detailDisabled = registerTexture("romfs:/png/detail/detial_disabled.png");
	//END REGISTER ASSETS
}

void MENU::init() {
	tabSelected = 0;
	menuSelected = 0;
	std::ostringstream version;
	version << 'v' << VERSION_MAJOR << '.' << VERSION_MINOR << '.' << VERSION_MICRO;
	gfxDrawText(background->tex, version.str().c_str(), versionFont->fnt, 380, 59, 18, RGBA8(194, 17, 170, 0));
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
	gfxBlit(frameBuffer, background->tex, 0, 0);
	gfxBlit(frameBuffer, tabSelected == 0 ? tabKipsSelected->tex : tabKips->tex, 560, 118);
	gfxBlit(frameBuffer, tabSelected == 1 ? tabBCTSelected->tex : tabBCT->tex, 683, 118);
	gfxBlit(frameBuffer, tabSelected == 2 ? tabLayeredFSSelected->tex : tabLayeredFS->tex, 843, 118);
	gfxBlit(frameBuffer, tabSelected == 3 ? tabOptionsSelected->tex : tabOptions->tex, 1088, 118);
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
		//HANDLE SCROLLING
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
		//~~
		//DRAW MENU LIST
		for (unsigned int i = offset; i < offsetLimit; i++) {
			unsigned int drawY = 178 + ((i - offset) * 64);
			if (i == menuSelected) {
				gfxBlit(frameBuffer, menuBarSelected->tex, 0, drawY);
			}
			else {
				gfxBlit(frameBuffer, menuBar->tex, 0, drawY);
			}
			if ((*mnu)[i].status) {
				gfxBlit(frameBuffer, checkmark->tex, 825, drawY + 16);
			}
			gfxDrawText(frameBuffer, (*mnu)[i].name.c_str(), mainFont->fnt, 16, drawY + 16, 32, RGBA8(255, 255, 255, 0));
		}
		//~~
		//DRAW SCROLL INDICATOR
		if (offset > 0) {
			gfxBlit(frameBuffer, menuScrollUp->tex, 858, 172);
		}
		if (offsetLimit < mnu->size()) {
			gfxBlit(frameBuffer, menuScrollDown->tex, 858, 686);
		}
		//~~
		//DRAW DETAILS WINDOW
		gfxDrawText(frameBuffer, (*mnu)[menuSelected].name.c_str(), mainFont->fnt, 905, 178, 18, RGBA8(255, 255, 255, 0));
		for (unsigned int i = 0; i < (*mnu)[menuSelected].details.size(); i++) {
			unsigned int curY = i * 18 + 202;
			std::ostringstream ss;
			ss << (*mnu)[menuSelected].details[i].prefix << (*mnu)[menuSelected].details[i].data << (*mnu)[menuSelected].details[i].suffix;
			gfxDrawTextWrap(frameBuffer, ss.str().c_str(), mainFont->fnt, 905, curY, 12, RGBA8(255, 255, 255, 0), 370);
		}
		if ((*mnu)[menuSelected].status) {
			gfxBlit(frameBuffer, detailEnabled->tex, 972, 652);
		}
		else {
			gfxBlit(frameBuffer, detailDisabled->tex, 972, 652);
		}
		//~~
	}
}