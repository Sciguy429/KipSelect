#include <switch.h>

#include "screen/thread/render.h"
#include "screen/gfx.h"

void renderThread(void *vector) {
	unsigned int red = 0;
	unsigned int green = 0;
	unsigned int blue = 0;
	unsigned int itr = 0;
	//END
	renderThreadControlVector *rTCV = (renderThreadControlVector*)vector;
	printf("RENDER -- Render Thread Starting\nRENDER -- Running On Core: %d\n", svcGetCurrentProcessorNumber());
	while (rTCV->runThread) {
		u64 start;
		u64 end;
		start = svcGetSystemTick();
		while (true) {
			if (red == 255) {
				if (blue == 255) {
					if (green == 255) {
						if (blue == 255) {
							red = 0;
							green = 0;
							blue = 0;
							break;
						}
					}
					else {
						green++;
					}
				}
				else {
					blue++;
				}
			}
			else {
				red++;
			}
			itr++;
			gfxFill(frameBufferTexture, RGBA8(red, green, blue, 0));
			gfxDrawFrameBuffer();
		}
		end = svcGetSystemTick();
		u64 totalTick = end - start;
		u64 avgTick = totalTick / itr;
		u64 totalNano = armTicksToNs(totalTick);
		u64 avgNano = armTicksToNs(avgTick);
		long double avgSec = avgNano / 1000000000.0f;
		long double fps = 1.0f / avgSec;
		printf("RENDER -- %d Cycle's Completed In: %lu Ticks (%lu Nanoseconds)\n", itr, totalTick, totalNano);
		printf("RENDER -- Average Frame Time: %lu Ticks (%lu Nanoseconds)\n", avgTick, avgNano);
		printf("RENDER -- Average Frame Rate: %Lf Frames Per Second\n", fps);
		itr = 0;
	}
	printf("RENDER -- Thread Terminating\n");
}