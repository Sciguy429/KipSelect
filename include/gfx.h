#pragma once

typedef struct {
	size_t size;
	unsigned width, height;
	uint32_t *data;
} texture;

void gfxInit(unsigned int windowWidth, unsigned int windowHeight);

void gfxHandelBuffers();

void gfxDrawPixel(texture *tex, unsigned int x, unsigned int y, uint32_t clr);

void gfxDrawLine(texture *tex, unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, uint32_t clr);

void gfxDrawVerticalLine(texture *tex, unsigned int x, unsigned int y, unsigned int length, uint32_t clr);

void gfxDrawHorizontalLine(texture *tex, unsigned int x, unsigned int y, unsigned int length, uint32_t clr);

void gfxDrawRect(texture *tex, unsigned int tx, unsigned int ty, unsigned int bx, unsigned int by, uint32_t clr, bool fill);

extern texture *frameBuffer;