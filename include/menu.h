#pragma once

#include <switch.h>
#include <string>
#include <vector>

#include "load.h"

typedef struct {
	std::string prefix;
	std::string data;
	std::string suffix;
} menuDetail;

typedef struct {
	std::string name;
	std::vector<menuDetail> details;
	bool status;
} menuItem;

class MENU {
public:
	void registerAssets();
	void init();
	void setTabSelected(unsigned int tabId);
	unsigned int getTabSelected();
	void setMenuSelected(unsigned int menuId);
	unsigned int getMenuSelected();
	unsigned int getMenuSize();
	void toggleSelected();
	void addMenuItem(unsigned int tab, menuItem itm);
	void resetMenu();
	void drawMenu();
private:
	unsigned int tabSelected;
	unsigned int menuSelected;
	std::vector<menuItem> kips;
	std::vector<menuItem> bct;
	std::vector<menuItem> layeredFS;
	std::vector<menuItem> options;
	//ASSETS
	//-Texture
	regTex *background;
	regTex *menuBar;
	regTex *menuBarSelected;
	regTex *checkmark;
	regTex *questionmark;
	regTex *menuScrollUp;
	regTex *menuScrollDown;
	regTex *tabKips;
	regTex *tabKipsSelected;
	regTex *tabBCT;
	regTex *tabBCTSelected;
	regTex *tabLayeredFS;
	regTex *tabLayeredFSSelected;
	regTex *tabOptions;
	regTex *tabOptionsSelected;
	regTex *detailEnabled;
	regTex *detailDisabled;
	//regTex *detailLoaded;
	//regTex *detailUnloaded;
	//-Font
	regFnt *mainFont;
	regFnt *versionFont;
};