#pragma once

//

void gfxInit(int windowWidth, int windowHeight);

void gfxHandelBuffers();

void gfxDrawPixel(int x, int y, uint32_t clr);

void gfxDrawLine(int x0, int y0, int x1, int y1, uint32_t clr);

void gfxDrawVerticalLine(int x, int y, int length, uint32_t clr);

void gfxDrawHorizontalLine(int x, int y, int lenght, uint32_t clr);

void gfxDrawRect(int tx, int ty, int bx, int by, uint32_t clr, bool fill);