#include <switch.h>

#include "screen/thread/render.h"
#include "screen/gfx.h"
#include "utils/timer.h"

void renderThread(void *vector) {
	renderThreadControlVector *rTCV = (renderThreadControlVector*)vector;
	printf("RENDER -- Render Thread Starting\nRENDER -- Running On Core: %d\n", svcGetCurrentProcessorNumber());
	TIMER timer = TIMER();
	trigger *test = timer.createTrigger(NS_TO_TICKS(1000000000), 60);
	while (rTCV->runThread) {
		//Render
		timer.update();
		if (test->count > 0) {
			test->reset();
			printf("RENDER -- Trigger Detected!\n");
		}
	}
	printf("RENDER -- Thread Terminating\n");
}