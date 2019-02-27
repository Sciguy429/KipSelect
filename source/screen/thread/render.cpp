#include <switch.h>

#include "screen/thread/render.h"
#include "screen/gfx.h"

void renderThread(void *vector) {
	renderThreadControlVector *rTCV = (renderThreadControlVector*)vector;
	printf("RENDER -- Render Thread Starting\nRENDER -- Running On Core: %d\n", svcGetCurrentProcessorNumber());
	while (rTCV->runThread) {
		//Render
	}
	printf("RENDER -- Thread Terminating\n");
}