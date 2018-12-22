#include <vector>

#include "load.h"

std::vector<regTex> registeredTextures;
std::vector<regFnt> registeredFonts;

regTex *registerTexture(std::string path) {
	unsigned int pos = registeredTextures.size();
	registeredTextures.push_back(regTex());
	registeredTextures[pos].path = path;
	return &registeredTextures[pos];
}

regFnt *registerFont(std::string path) {
	unsigned int pos = registeredFonts.size();
	registeredFonts.push_back(regFnt());
	registeredFonts[pos].path = path;
	return &registeredFonts[pos];
}

void loadRegistered() {
	for (unsigned int i = 0; i < registeredTextures.size(); i++) {
		registeredTextures[i].tex = gfxCreateTextureFromPNG(registeredTextures[i].path.c_str());
	}
	for (unsigned int i = 0; i < registeredFonts.size(); i++) {
		registeredFonts[i].fnt = gfxCreateFontFromTTF(registeredFonts[i].path.c_str());
	}
}

void destroyRegistered() {
	for (unsigned int i = 0; i < registeredTextures.size(); i++) {
		gfxDestroyTexture(registeredTextures[i].tex);
	}
	for (unsigned int i = 0; i < registeredFonts.size(); i++) {
		gfxDestroyFont(registeredFonts[i].fnt);
	}
}
