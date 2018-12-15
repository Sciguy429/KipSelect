#include <switch.h>
#include <stdlib.h>

#include "gfx.h"

u32* framebuf;

void gfxInit(int windowWidth, int windowHeight) {
	gfxInitResolution((uint32_t)windowWidth, (uint32_t)windowHeight);
	gfxInitDefault();
	consoleInit(NULL);
	gfxSetMode(GfxMode_LinearDouble);
}

void gfxHandelBuffers() {
	gfxFlushBuffers();
	gfxSwapBuffers();
	gfxWaitForVsync();
}

void gfxDrawPixel(int x, int y, uint32_t clr) {
	u32 width, height;
	framebuf = (u32*)gfxGetFramebuffer((u32*)&width, (u32*)&height);
	framebuf[y * width + x] = clr;
}

void gfxDrawLine(int x0, int y0, int x1, int y1, uint32_t clr) {
	int x = x1 - x0;
	int y = y1 - y0;
	int dx = abs(x), sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y), sy = y0 < y1 ? 1 : -1;
	int err = dx + dy, e2;
	for (;;) {
		gfxDrawPixel(x0, y0, clr);
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

void gfxDrawVerticalLine(int x, int y, int length, uint32_t clr) {
	for (int i = 0; i < length; i++) {
		gfxDrawPixel(x, y + i, clr);
	}
}

void gfxDrawHorizontalLine(int x, int y, int lenght, uint32_t clr) {
	for (int i = 0; i < lenght; i++) {
		gfxDrawPixel(x + i, y, clr);
	}
}

void gfxDrawRect(int tx, int ty, int bx, int by, uint32_t clr, bool fill) {
	int length = bx - tx;
	int width = by - ty;
	if (fill) {
		for (int i = 0; i < length; i++) {
			gfxDrawVerticalLine(tx + i, ty, width, clr);
		}
	}
	else {
		gfxDrawHorizontalLine(tx, ty, length, clr);
		gfxDrawHorizontalLine(tx, ty + width, length, clr);
		gfxDrawVerticalLine(tx, ty, width, clr);
		gfxDrawVerticalLine(tx + length, ty, width, clr);
	}
}