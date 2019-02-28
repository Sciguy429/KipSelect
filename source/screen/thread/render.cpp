#include <switch.h>

#include "screen/thread/render.h"
#include "screen/gfx.h"

#include <vector>
#include <sstream>

void renderThread(void *vector) {
	renderThreadControlVector *rTCV = (renderThreadControlVector*)vector;

	std::vector<texture*> textures;

	printf("RENDER -- Render Thread Starting\nRENDER -- Running On Core: %d\n", svcGetCurrentProcessorNumber());
	for (int i = 0; i < 60; i++) {
		printf("RENDER -- %d of 60\n", i + 1);
		std::ostringstream ss;
		ss << "romfs:/png/test/gear_" << i + 1 << ".png";
		textures.push_back(gfxCreateTextureFromPNG(ss.str().c_str()));
	}
	while (rTCV->runThread) {
		//Render
		for (unsigned int i = 0; i < textures.size(); i++) {
			gfxFill(frameBufferTexture, RGBA8(0, 0, 0, 0));
			gfxBlit(frameBufferTexture, textures[i], 0, 0);
			gfxDrawFrameBuffer();
		}
	}
	for (unsigned int i = 0; i < textures.size(); i++) {
		gfxDestroyTexture(textures[i]);
	}
	printf("RENDER -- Thread Terminating\n");
}