#pragma once

//

void gfxInit(int windowWidth, int windowHeight);

void gfxHandelBuffers();

void gfxDrawPixel(int x, int y, uint32_t clr);

void gfxDrawRect(int tx, int ty, int bx, int by, uint32_t clr, bool fill);