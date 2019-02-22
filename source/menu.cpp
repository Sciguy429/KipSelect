#include <switch.h>
#include <sstream>

#include "menu.h"

void MENU::loadAssets() {
	tabSelected = 0;
	menuSelected = 0;
	//LOAD ASSETS
	//-Fonts
	mainFont = gfxCreateFontFromTTF("romfs:/font/bahnschrift.ttf");
	font *versionFont = gfxCreateFontFromTTF("romfs:/font/tt0288m_.ttf");
	//-Textures
	menuBackground = gfxCreateTextureFromPNG("romfs:/png/menu/menu_background.png");
	menuBar = gfxCreateTextureFromPNG("romfs:/png/menu/menu_bar.png");
	menuBarSelected = gfxCreateTextureFromPNG("romfs:/png/menu/menu_bar_selected.png");
	menuCheckmark = gfxCreateTextureFromPNG("romfs:/png/menu/menu_checkmark.png");
	menuQuestionmark = gfxCreateTextureFromPNG("romfs:/png/menu/menu_questionmark.png");
	menuScrollUp = gfxCreateTextureFromPNG("romfs:/png/menu/menu_scroll_up.png");
	menuScrollDown = gfxCreateTextureFromPNG("romfs:/png/menu/menu_scroll_down.png");
	tabKips = gfxCreateTextureFromPNG("romfs:/png/tab/tab_kips.png");
	tabKipsSelected = gfxCreateTextureFromPNG("romfs:/png/tab/tab_kips_selected.png");
	tabBCT = gfxCreateTextureFromPNG("romfs:/png/tab/tab_bct.png");
	tabBCTSelected = gfxCreateTextureFromPNG("romfs:/png/tab/tab_bct_selected.png");
	tabLayeredFS = gfxCreateTextureFromPNG("romfs:/png/tab/tab_layeredfs.png");
	tabLayeredFSSelected = gfxCreateTextureFromPNG("romfs:/png/tab/tab_layeredfs_selected.png");
	tabOptions = gfxCreateTextureFromPNG("romfs:/png/tab/tab_options.png");
	tabOptionsSelected = gfxCreateTextureFromPNG("romfs:/png/tab/tab_options_selected.png");
	detailPurple = gfxCreateTextureFromPNG("romfs:/png/detail/detail_purple.png");
	detailGray = gfxCreateTextureFromPNG("romfs:/png/detail/detail_gray.png");
	//END LOAD ASSETS
	//BUILD ASSETS
	//-Add Version To Backround
	std::ostringstream version;
	version << 'v' << VERSION_MAJOR << '.' << VERSION_MINOR << '.' << VERSION_MICRO;
	gfxDrawText(menuBackground, version.str().c_str(), versionFont, 380, 59, 18, RGBA8(194, 17, 170, 0));
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

inline unsigned int MENU::getMenuSize() {
	switch (tabSelected) {
	case 0:
		return kip.size();
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

void MENU::setStatusSelected(unsigned int statusId) {
	std::vector<menuItem> *mnu = new std::vector<menuItem>;
	switch (tabSelected) {
	case 0:
		mnu = &kip;
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
	(*mnu)[menuSelected].statusSelected = statusId;
}

unsigned int MENU::getStatusSelected() {
	std::vector<menuItem> *mnu = new std::vector<menuItem>;
	switch (tabSelected) {
	case 0:
		mnu = &kip;
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
		return 0;
	}
	return (*mnu)[menuSelected].statusSelected;
}

unsigned int MENU::getStatusCount() {
	std::vector<menuItem> *mnu = new std::vector<menuItem>;
	switch (tabSelected) {
	case 0:
		mnu = &kip;
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
		return 0;
	}
	return (*mnu)[menuSelected].statuses.size();
}
/*
void MENU::toggleSelected() {
	std::vector<menuItem> *mnu = new std::vector<menuItem>;
	switch (tabSelected) {
	case 0:
		mnu = &kip;
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
*/

void MENU::addMenuItem(unsigned int tab, menuItem itm) {
	std::vector<menuItem> *mnu = new std::vector<menuItem>;
	switch (tab) {
	case 0:
		mnu = &kip;
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
	kip.clear();
	bct.clear();
	layeredFS.clear();
	options.clear();
}

void MENU::drawMenu() {
	/*
	gfxBlit(frameBufferTexture, menuBackground, 0, 0);
	gfxBlit(frameBufferTexture, tabSelected == 0 ? tabKipsSelected : tabKips, 560, 118);
	gfxBlit(frameBufferTexture, tabSelected == 1 ? tabBCTSelected : tabBCT, 683, 118);
	gfxBlit(frameBufferTexture, tabSelected == 2 ? tabLayeredFSSelected : tabLayeredFS, 843, 118);
	gfxBlit(frameBufferTexture, tabSelected == 3 ? tabOptionsSelected : tabOptions, 1088, 118);
	std::vector<menuItem> *mnu = new std::vector<menuItem>;
	switch (tabSelected) {
	case 0:
		mnu = &kip;
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
				gfxBlit(frameBufferTexture, menuBarSelected, 0, drawY);
			}
			else {
				gfxBlit(frameBufferTexture, menuBar, 0, drawY);
			}
			if ((*mnu)[i].status) {
				gfxBlit(frameBufferTexture, menuCheckmark, 825, drawY + 16);
			}
			gfxDrawText(frameBufferTexture, (*mnu)[i].name.c_str(), mainFont, 16, drawY + 16, 32, RGBA8(255, 255, 255, 0));
		}
		//~~
		//DRAW SCROLL INDICATOR
		if (offset > 0) {
			gfxBlit(frameBufferTexture, menuScrollUp, 858, 172);
		}
		if (offsetLimit < mnu->size()) {
			gfxBlit(frameBufferTexture, menuScrollDown, 858, 686);
		}
		//~~
		//DRAW DETAILS WINDOW
		std::ostringstream name;
		if ((*mnu)[menuSelected].name.length() > 30) {
			name << (*mnu)[menuSelected].name.substr(0, 27) << "...";
		}
		else {
			name << (*mnu)[menuSelected].name;
		}
		gfxDrawTextCenter(frameBufferTexture, name.str().c_str(), mainFont, 1090, 178, 22, RGBA8(255, 255, 255, 0));
		for (unsigned int i = 0; i < (*mnu)[menuSelected].details.size(); i++) {
			unsigned int curY = i * 18 + 216;
			std::ostringstream detail;
			detail << (*mnu)[menuSelected].details[i].prefix << (*mnu)[menuSelected].details[i].data << (*mnu)[menuSelected].details[i].suffix;
			gfxDrawTextWrap(frameBufferTexture, detail.str().c_str(), mainFont, 905, curY, 12, RGBA8(255, 255, 255, 0), 370);
		}
		if ((*mnu)[menuSelected].status) {
			gfxBlit(frameBufferTexture, detailEnabled, 972, 652);
		}
		else {
			gfxBlit(frameBufferTexture, detailDisabled, 972, 652);
		}
		//~~
	}
	gfxDrawFrameBuffer();
	*/
}

void MENU::destroyAssets() {
	gfxDestroyFont(mainFont);
	gfxDestroyTexture(menuBackground);
	gfxDestroyTexture(menuBar);
	gfxDestroyTexture(menuBarSelected);
	gfxDestroyTexture(menuCheckmark);
	gfxDestroyTexture(menuQuestionmark);
	gfxDestroyTexture(menuScrollUp);
	gfxDestroyTexture(menuScrollDown);
	gfxDestroyTexture(tabKips);
	gfxDestroyTexture(tabKipsSelected);
	gfxDestroyTexture(tabBCT);
	gfxDestroyTexture(tabBCTSelected);
	gfxDestroyTexture(tabLayeredFS);
	gfxDestroyTexture(tabLayeredFSSelected);
	gfxDestroyTexture(tabOptions);
	gfxDestroyTexture(tabOptionsSelected);
	gfxDestroyTexture(detailPurple);
	gfxDestroyTexture(detailGray);
}

menuItem *MENU::getSelectedItem() {
	std::vector<menuItem> *mnu = new std::vector<menuItem>;
	switch (tabSelected) {
	case 0:
		mnu = &kip;
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
		return NULL;
	}
	return &mnu->at(menuSelected);
}