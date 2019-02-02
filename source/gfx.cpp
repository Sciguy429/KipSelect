#include <switch.h>
#include <string>
#include <stdlib.h>
#include <png.h>

#include "gfx.h"

texture *frameBufferTexture;
Framebuffer frameBuffer;

static uint32_t colorBlendAlpha(uint32_t colorA, uint32_t colorB) {
	uint8_t aA = colorA >> 24 & 0xFF;
	if (aA == 0x00) {
		return colorB;
	}
	if (aA == 0xFF) {
		return colorA;
	}
	uint8_t aR = colorA & 0xFF;
	uint8_t aG = colorA >> 8 & 0xFF;
	uint8_t aB = colorA >> 16 & 0xFF;
	uint8_t bR = colorB & 0xFF;
	uint8_t bG = colorB >> 8 & 0xFF;
	uint8_t bB = colorB >> 16 & 0xFF;
	uint8_t fA = 0xFF - aA;
	uint8_t fR = (aR * aA + bR * fA) / 0xFF;
	uint8_t fG = (aG * aA + bG * fA) / 0xFF;
	uint8_t fB = (aB * aA + bB * fA) / 0xFF;
	return (0xFF << 24 | fB << 16 | fG << 8 | fR);
}

static uint32_t colorReplaceAlpha(uint32_t clr, uint8_t alpha) {
	uint8_t r = clr & 0xFF;
	uint8_t g = clr >> 8 & 0xFF;
	uint8_t b = clr >> 16 & 0xFF;
	return (alpha << 24 | b << 16 | g << 8 | r);
}

static void drawGlyph(texture *tex, const FT_Bitmap *ftBmp, int posX, int posY, uint32_t clr) {
	if (ftBmp->pixel_mode != FT_PIXEL_MODE_GRAY) {
		return;
	}
	uint8_t *ftBmpPtr = ftBmp->buffer;
	for (int y = posY; y < posY + ftBmp->rows; y++) {
		if (y > tex->height || y < 0) {
			continue;
		}
		uint32_t *rowPtr = &tex->data[y * tex->width + posX];
		for (int x = posX; x < posX + ftBmp->width; x++, ftBmpPtr++, rowPtr++) {
			if (x > tex->width || x < 0) {
				continue;
			}
			if (*ftBmpPtr > 0) {
				*rowPtr = colorBlendAlpha(colorReplaceAlpha(clr, *ftBmpPtr), *rowPtr);
			}
		}
	}
}

static void resizeFont(const font *fnt, int size) {
	FT_Set_Char_Size(fnt->face, 0, size * 64, 90, 90);
}

static FT_GlyphSlot loadGlyph(const uint32_t charId, const font *fnt, FT_Int32 flags) {
	FT_Load_Glyph(fnt->face, FT_Get_Char_Index(fnt->face, charId), flags);
	return fnt->face->glyph;
}

static size_t getTextLength(const char *text, const font *fnt, int size) {
	size_t width = 0;
	uint32_t unitCount = 0;
	uint32_t tmpChar = 0;
	resizeFont(fnt, size);
	size_t textLength = strlen(text);
	for (unsigned int i = 0; i < textLength;) {
		unitCount = decode_utf8(&tmpChar, (const uint8_t*)&text[i]);
		if (unitCount <= 0) {
			break;
		}
		i += unitCount;
		FT_GlyphSlot slot = loadGlyph(tmpChar, fnt, FT_LOAD_DEFAULT);
		width += slot->advance.x >> 6;
	}
	return width;
}

void gfxInit(unsigned int windowWidth, unsigned int windowHeight) {
	NWindow* win = nwindowGetDefault();
	framebufferCreate(&frameBuffer, win, windowWidth, windowHeight, PIXEL_FORMAT_RGBA_8888, 2);
	framebufferMakeLinear(&frameBuffer);
	frameBufferTexture = gfxCreateTexture(windowWidth, windowHeight);
}

void gfxCleanUp() {
	gfxDestroyTexture(frameBufferTexture);
	framebufferClose(&frameBuffer);
}

void gfxDrawFrameBuffer() {
	u32 stride;
	u32* fb = (u32*)framebufferBegin(&frameBuffer, &stride);
	uint32_t *dataPtr = &frameBufferTexture->data[0];
	for (unsigned int y = 0; y < frameBufferTexture->height; y++) {
		uint32_t *rowPtr = &fb[y * stride / sizeof(u32)];
		for (unsigned int x = 0; x < frameBufferTexture->width; x++, dataPtr++, rowPtr++) {
			*rowPtr = *dataPtr;
		}
	}
	framebufferEnd(&frameBuffer);
}

void gfxDrawPixel(texture *tex, unsigned int x, unsigned int y, uint32_t clr) {
	if (x < tex->width && y < tex->height) {
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

void gfxDrawText(texture *tex, const char *text, const font *fnt, int x, int y, int size, uint32_t clr) {
	int curX = x;
	uint32_t tmpChar = 0;
	ssize_t unitCount = 0;
	resizeFont(fnt, size);
	size_t length = strlen(text);
	bool bold = false;
	for (unsigned int i = 0; i < length;) {
		unitCount = decode_utf8(&tmpChar, (const uint8_t*)&text[i]);
		if (unitCount <= 0) {
			break;
		}
		i += unitCount;
		switch (tmpChar) {
		case '\n': //Newline
			curX = x;
			y += size + 8;
			continue;
		case '^': //Bold Toggle
			bold = !bold;
			continue;
		}
		FT_GlyphSlot slot = loadGlyph(tmpChar, fnt, FT_LOAD_RENDER);
		if (slot != NULL) {
			int drawY = y + (size - slot->bitmap_top);
			drawGlyph(tex, &slot->bitmap, curX + slot->bitmap_left, drawY, clr);
			if (bold) {
				drawGlyph(tex, &slot->bitmap, curX + slot->bitmap_left + 1, drawY + 1, clr);
			}
			curX += slot->advance.x >> 6;
		}
	}
}

void gfxDrawTextWrap(texture *tex, const char *text, const font *fnt, int x, int y, int size, uint32_t clr, int maxLength) {
	char wordBuf[128];
	size_t nextBreak = 0;
	size_t textLength = strlen(text);
	int curX = x;
	bool bold = false;
	for (unsigned int i = 0; i < textLength;) {
		nextBreak = strcspn(&text[i], " /");
		memset(wordBuf, 0, 128);
		memcpy(wordBuf, &text[i], nextBreak + 1);
		size_t width = getTextLength(wordBuf, fnt, size);
		if (curX + width >= x + maxLength) {
			curX = x;
			y += size + 8;
		}
		size_t wLength = strlen(wordBuf);
		uint32_t tmpChar = 0;
		for (unsigned int j = 0; j < wLength;) {
			ssize_t unitCount = decode_utf8(&tmpChar, (const uint8_t*)&wordBuf[j]);
			if (unitCount <= 0) {
				break;
			}
			j += unitCount;
			switch (tmpChar) {
			case '\n': //Newline
				curX = x;
				y += size + 8;
				continue;
			case '^': //Bold Toggle
				bold = !bold;
				continue;
			}
			FT_GlyphSlot slot = loadGlyph(tmpChar, fnt, FT_LOAD_RENDER);
			if (slot != NULL) {
				int drawY = y + (size - slot->bitmap_top);
				drawGlyph(tex, &slot->bitmap, curX + slot->bitmap_left, drawY, clr);
				if (bold) {
					drawGlyph(tex, &slot->bitmap, curX + slot->bitmap_left + 1, drawY + 1, clr);
				}
				curX += slot->advance.x >> 6;
			}
		}
		i += strlen(wordBuf);
	}
}

void gfxDrawTextCenter(texture *tex, const char *text, const font *fnt, int x, int y, int size, uint32_t clr) {
	size_t length = getTextLength(text, fnt, size);
	gfxDrawText(tex, text, fnt, x - length / 2, y, size, clr);
}

void gfxFill(texture *tex, uint32_t clr) {
	uint32_t *dataPtr = &tex->data[0];
	for (unsigned int y = 0; y < tex->height; y++) {
		for (unsigned int x = 0; x < tex->width; x++) {
			*dataPtr++ = clr;
		}
	}
}

void gfxBlit(texture *target, texture *source, unsigned int x, unsigned int y) {
	if (source != NULL) {
		uint32_t *dataPtr = &source->data[0];
		for (unsigned int ty = y; ty < y + source->height; ty++) {
			uint32_t *rowPtr = &target->data[ty * target->width + x];
			for (unsigned int tx = x; tx < x + source->width; tx++, dataPtr++, rowPtr++) {
				if (tx < target->width && ty < target->height) {
					*rowPtr = colorBlendAlpha(*dataPtr, *rowPtr);
				}
			}
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
	printf("Created empty %d by %d texture at address %p\n", width, height, (void*)tex);
	return tex;
}

texture *gfxCreateTextureFromPNG(const char *path) {
	FILE *pngFile = fopen(path, "rb");
	if (pngFile != NULL) {
		png_structp pngReadStruct = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
		if (pngReadStruct == 0) {
			return NULL;
		}
		png_infop pngInfoStruct = png_create_info_struct(pngReadStruct);
		if (pngInfoStruct == 0) {
			return NULL;
		}
		int pngJmp = setjmp(png_jmpbuf(pngReadStruct));
		if (pngJmp) {
			return NULL;
		}
		png_init_io(pngReadStruct, pngFile);
		png_read_info(pngReadStruct, pngInfoStruct);
		if (png_get_color_type(pngReadStruct, pngInfoStruct) != PNG_COLOR_TYPE_RGBA) {
			png_destroy_read_struct(&pngReadStruct, &pngInfoStruct, NULL);
			return NULL;
		}
		texture *tex = (texture*)malloc(sizeof(texture));
		tex->width = png_get_image_width(pngReadStruct, pngInfoStruct);
		tex->height = png_get_image_height(pngReadStruct, pngInfoStruct);
		tex->data = (uint32_t*)malloc((tex->width * tex->height) * sizeof(uint32_t));
		tex->size = tex->width * tex->height;
		png_bytep *rows = (png_bytep*)malloc(sizeof(png_bytep) * tex->height);
		for (unsigned int i = 0; i < tex->height; i++) {
			rows[i] = (png_bytep)malloc(png_get_rowbytes(pngReadStruct, pngInfoStruct));
		}
		png_read_image(pngReadStruct, rows);
		uint32_t *dataPtr = &tex->data[0];
		for (unsigned int y = 0; y < tex->height; y++) {
			uint32_t *rowPtr = (uint32_t*)rows[y];
			for (unsigned int x = 0; x < tex->width; x++) {
				*dataPtr++ = *rowPtr++;
			}
		}
		for (unsigned int i = 0; i < tex->height; i++) {
			free(rows[i]);
		}
		free(rows);
		png_destroy_read_struct(&pngReadStruct, &pngInfoStruct, NULL);
		fclose(pngFile);
		printf("Created texture from %s at address %p\n", path, (void*)tex);
		return tex;
	}
	return NULL;
}

void gfxDestroyTexture(texture *tex) {
	if (tex->data != NULL) {
		free(tex->data);
	}
	if (tex != NULL) {
		free(tex);
	}
	printf("Destroyed texture at address %p\n", (void*)tex);
}

font *gfxCreateFontFromTTF(const char *path) {
	font *fnt = (font*)malloc(sizeof(font));
	if ((fnt->libRet = FT_Init_FreeType(&fnt->lib))) {
		free(fnt);
		return NULL;
	}
	FILE *ttfFile = fopen(path, "rb");
	fseek(ttfFile, 0, SEEK_END);
	size_t ttfFileSize = ftell(ttfFile);
	fseek(ttfFile, 0, SEEK_SET);
	fnt->data = (uint8_t*)malloc(ttfFileSize);
	fread(fnt->data, 1, ttfFileSize, ttfFile);
	fclose(ttfFile);
	if ((fnt->faceRet = FT_New_Memory_Face(fnt->lib, fnt->data, ttfFileSize, 0, &fnt->face))) {
		free(fnt->data);
		free(fnt);
		return NULL;
	}
	printf("Created font from %s at address %p\n", path, (void*)fnt);
	return fnt;
}

void gfxDestroyFont(font *fnt) {
	if (fnt->faceRet == 0) {
		FT_Done_Face(fnt->face);
	}
	if (fnt->libRet == 0) {
		FT_Done_FreeType(fnt->lib);
	}
	if (fnt->data != NULL) {
		free(fnt->data);
	}
	free(fnt);
	printf("Destroyed font at address %p\n", (void*)fnt);
}