#include <switch.h>

#include "gfx.h"

u32* framebuf;

void gfxInit(int windowWidth, int windowHeight) {
	gfxInitResolution((uint32_t) windowWidth, (uint32_t) windowHeight);
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
	framebuf = (u32*) gfxGetFramebuffer((u32*) &width, (u32*) &height);
	framebuf[y * width + x] = clr;
}

void gfxDrawRect(int tx, int ty, int bx, int by, uint32_t clr, bool fill) {
	//stub
}