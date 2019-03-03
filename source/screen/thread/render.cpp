#include <switch.h>

#include "screen/thread/render.h"
#include "screen/gfx.h"
#include "utils/timer.h"

void renderThread(void *vector) {
	renderThreadControlVector *rTCV = (renderThreadControlVector*)vector;
	printf("RENDER -- Render Thread Starting\nRENDER -- Running On Core: %d\n", svcGetCurrentProcessorNumber());
	TIMER timer = TIMER();
	trigger *test1 = timer.createTrigger(NS_TO_TICKS(1000000000), 60);
	trigger *test2 = timer.createTrigger(NS_TO_TICKS(500000000), 60);
	trigger *test3 = timer.createTrigger(NS_TO_TICKS(500000000), 60);
	while (rTCV->runThread) {
		//Render
		timer.update();
		if (test1->count > 0) {
			test1->reset();
			printf("RENDER -- Trigger #1 Detected!\n");
		}
		if (test2->count > 0) {
			test2->reset();
			printf("RENDER -- Trigger #2 Detected!\n");
		}
		if (test3->count > 0) {
			test3->reset();
			printf("RENDER -- Trigger #3 Detected!\n");
		}
	}
	printf("RENDER -- Thread Terminating\n");
}