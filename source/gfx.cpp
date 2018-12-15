#include <switch.h>
#include <cstring>
#include <stdlib.h>

#include "gfx.h"

texture *frameBuffer;

unsigned int colorBlendAlpha(unsigned int colora, unsigned int colorb, unsigned int alpha) {
	unsigned int rb1 = ((0x100 - alpha) * (colora & 0xFF00FF)) >> 8;
	unsigned int rb2 = (alpha * (colorb & 0xFF00FF)) >> 8;
	unsigned int g1 = ((0x100 - alpha) * (colora & 0x00FF00)) >> 8;
	unsigned int g2 = (alpha * (colorb & 0x00FF00)) >> 8;
	return ((rb1 | rb2) & 0xFF00FF) + ((g1 | g2) & 0x00FF00);
}

void gfxInit(unsigned int windowWidth, unsigned int windowHeight) {
	gfxInitResolution((uint32_t)windowWidth, (uint32_t)windowHeight);
	gfxInitDefault();
	consoleInit(NULL);
	gfxSetMode(GfxMode_LinearDouble);
	frameBuffer = (texture*)malloc(sizeof(texture));
	frameBuffer->width = windowWidth;
	frameBuffer->height = windowHeight;
	frameBuffer->data = (uint32_t*)gfxGetFramebuffer(NULL, NULL);
	frameBuffer->size = windowWidth * windowHeight;
}

void gfxCleanUp() {
	free(frameBuffer);
	gfxExit();
}

void gfxHandelBuffers() {
	gfxFlushBuffers();
	gfxSwapBuffers();
	gfxWaitForVsync();
}

void gfxDrawPixel(texture *tex, unsigned int x, unsigned int y, uint32_t clr) {
	if ((x < tex->width) && (y < tex->height)) {
		tex->data[y * tex->width + x] = clr;
	}
}

void gfxDrawLine(texture *tex, unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, uint32_t clr) {
	int x = x1 - x0;
	int y = y1 - y0;
	int dx = abs(x), sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y), sy = y0 < y1 ? 1 : -1;
	int err = dx + dy, e2;
	for (;;) {
		gfxDrawPixel(tex, x0, y0, clr);
		e2 = 2 * err;
		if (e2 >= dy) {
			if (x0 == x1) break;
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx) {
			if (y0 == y1) break;
			err += dx;
			y0 += sy;
		}
	}
}

void gfxDrawVerticalLine(texture *tex, unsigned int x, unsigned int y, unsigned int length, uint32_t clr) {
	for (unsigned int i = 0; i < length; i++) {
		gfxDrawPixel(tex, x, y + i, clr);
	}
}

void gfxDrawHorizontalLine(texture *tex, unsigned int x, unsigned int y, unsigned int length, uint32_t clr) {
	for (unsigned int i = 0; i < length; i++) {
		gfxDrawPixel(tex, x + i, y, clr);
	}
}

void gfxDrawRect(texture *tex, unsigned int tx, unsigned int ty, unsigned int bx, unsigned int by, uint32_t clr, bool fill) {
	int length = bx - tx;
	int width = by - ty;
	if ((length > 0) || (width > 0)) {
		if (fill) {
			for (int i = 0; i < length; i++) {
				gfxDrawVerticalLine(tex, tx + i, ty, width, clr);
			}
		}
		else {
			gfxDrawHorizontalLine(tex, tx, ty, length, clr);
			gfxDrawHorizontalLine(tex, tx, ty + width, length, clr);
			gfxDrawVerticalLine(tex, tx, ty, width, clr);
			gfxDrawVerticalLine(tex, tx + length, ty, width, clr);
		}
	}
}

texture *gfxCreateTexture(unsigned int width, unsigned int height) {
	texture *tex = (texture*)malloc(sizeof(texture));
	tex->width = width;
	tex->height = height;
	tex->data = (uint32_t*)malloc(width * height * sizeof(uint32_t));
	memset(tex->data, 0, width * height * sizeof(uint32_t));
	tex->size = tex->width * tex->height;
	return tex;
}

void gfxDestroyTexture(texture *tex) {
	if (tex->data != NULL) {
		free(tex->data);
	}
	if (tex != NULL) {
		free(tex);
	}
}

texture *gfxTextureLoadPNG(std::string path) {
	//stub
	return NULL;
}

void gfxTextureBlit(texture *target, texture *source, unsigned int x, unsigned int y) {
	if (source != NULL) {
		uint32_t *dataPtr = &source->data[0];
		for (unsigned int ty = y; ty < y + source->height; ty++) {
			uint32_t *rowPtr = &target->data[ty * target->width + x];
			for (unsigned int tx = x; tx < x + source->width; tx++, rowPtr++) {
				*rowPtr = colorBlendAlpha(*dataPtr++, *rowPtr, 0);
			}
		}
	}
}