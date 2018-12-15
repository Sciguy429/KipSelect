#pragma once

typedef struct {
	size_t size;
	unsigned width, height;
	uint32_t *data;
} texture;

unsigned int colorBlendAlpha(unsigned int colora, unsigned int colorb, unsigned int alpha);

void gfxInit(unsigned int windowWidth, unsigned int windowHeight);

void gfxCleanUp();

void gfxHandelBuffers();

void gfxDrawPixel(texture *tex, unsigned int x, unsigned int y, uint32_t clr);

void gfxDrawLine(texture *tex, unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, uint32_t clr);

void gfxDrawVerticalLine(texture *tex, unsigned int x, unsigned int y, unsigned int length, uint32_t clr);

void gfxDrawHorizontalLine(texture *tex, unsigned int x, unsigned int y, unsigned int length, uint32_t clr);

void gfxDrawRect(texture *tex, unsigned int tx, unsigned int ty, unsigned int bx, unsigned int by, uint32_t clr, bool fill);

texture *gfxCreateTexture(unsigned int width, unsigned int height);

void gfxDestroyTexture(texture *tex);

texture *gfxCreateTextureFromPNG(const char *path);

void gfxTextureBlit(texture *target, texture *source, unsigned int x, unsigned int y, unsigned int alpha);

extern texture *frameBuffer;