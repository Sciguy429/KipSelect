#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

typedef struct {
	size_t size;
	unsigned width, height;
	uint32_t *data;
} texture;

typedef struct {
	FT_Library lib;
	FT_Face face;
	FT_Error libRet, faceRet;
	uint8_t *data;
} font;

void gfxInit(unsigned int windowWidth, unsigned int windowHeight);

void gfxCleanUp();

void gfxHandelBuffers();

void gfxDrawPixel(texture *tex, unsigned int x, unsigned int y, uint32_t clr);

void gfxDrawLine(texture *tex, unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, uint32_t clr);

void gfxDrawVerticalLine(texture *tex, unsigned int x, unsigned int y, unsigned int length, uint32_t clr);

void gfxDrawHorizontalLine(texture *tex, unsigned int x, unsigned int y, unsigned int length, uint32_t clr);

void gfxDrawRect(texture *tex, unsigned int tx, unsigned int ty, unsigned int bx, unsigned int by, uint32_t clr, bool fill);

void gfxDrawText(texture *tex, const char *text, const font *fnt, int x, int y, int size, uint32_t clr);

void gfxFill(texture *tex, uint32_t clr);

void gfxBlit(texture *target, texture *source, unsigned int x, unsigned int y);

texture *gfxCreateTexture(unsigned int width, unsigned int height);

texture *gfxCreateTextureFromPNG(const char *path);

void gfxDestroyTexture(texture *tex);

font *gfxCreateFontFromTTF(const char *path);

void gfxDestroyFont(font *fnt);

extern texture *frameBuffer;