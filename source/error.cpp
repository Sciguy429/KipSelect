#include <switch.h>
#include <stdarg.h>
#include <sstream>

#include "error.h"
#include "gfx.h"

bool errorThrown = false;
texture *errorBackground;
font *errorFont;

errorStructure errors[] = {
	{"Unable To Create Dirrectory", "Unable to create dirrectory: "}, //MKDIR_ERROR
	{"File Move Failed", "Unable to move file: "}, //RENAME_ERROR
	{"Unable To Open File", "Unable to write to file: "}, //OFSTREAM_ERROR
	{"Missing String In BCT.ini", "Unable to fine BCT target: "}, //BCT_LOCATION_ERROR
	{"Failed To Download File", "Unable to download file: "}, //CURL_GENERIC_ERROR
	{"Http Reponse Error", "Response code: "}, //CURL_HTTP_RESPONSE_ERROR
	{"Xml File Corrupted", "Unable to load data from Xml file: "}, //XML_ERROR
	{"Unable To Initialize Spl", "Response Code: "}, //SPL_INITILIZE_ERROR
	{"Failed To Configure Spl", "Response Code: "}, //SPL_CONFIGURATION_ERROR
	{"Payload File Not Found", "Could not find payload file: "} //PAYLOAD_NOT_FOUND_ERROR
};

void errorLoadAssets() {
	errorBackground = gfxCreateTextureFromPNG("romfs:/png/error/error_background.png");
	errorFont = gfxCreateFontFromTTF("romfs:/font/tt0288m_.ttf");
}

bool isErrorThrown() {
	return errorThrown;
}

void errorThrow(unsigned int errorType, const char *errorInfo) {
	errorThrown = true;
	gfxBlit(frameBufferTexture, errorBackground, 0, 0);
	gfxDrawTextCenter(frameBufferTexture, errors[errorType].header, errorFont, 640, 140, 32, RGBA8(255, 255, 255, 0));
	std::ostringstream ss;
	ss << errors[errorType].info << errorInfo;
	gfxDrawTextWrap(frameBufferTexture, ss.str().c_str(), errorFont, 40, 280, 32, RGBA8(255, 255, 255, 0), 1200);
	gfxDrawFrameBuffer();
	while (!(hidKeysDown(CONTROLLER_P1_AUTO) & KEY_PLUS)) {
		hidScanInput();
	}
}

void errorDestroyAssets() {
	gfxDestroyTexture(errorBackground);
	gfxDestroyFont(errorFont);
}
