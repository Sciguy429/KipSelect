#pragma once

//

void gfxInit(unsigned int windowWidth, unsigned int windowHeight);

void gfxHandelBuffers();

void gfxDrawPixel(unsigned int x, unsigned int y, uint32_t clr);

void gfxDrawLine(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, uint32_t clr);

void gfxDrawVerticalLine(unsigned int x, unsigned int y, unsigned int length, uint32_t clr);

void gfxDrawHorizontalLine(unsigned int x, unsigned int y, unsigned int length, uint32_t clr);

void gfxDrawRect(unsigned int tx, unsigned int ty, unsigned int bx, unsigned int by, uint32_t clr, bool fill);