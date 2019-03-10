#include <switch.h>
#include <math.h>

#include "screen/thread/render.h"
#include "screen/gfx.h"
#include "utils/timer.h"

void renderThread(void *vector) {
	renderThreadControlVector *rTCV = (renderThreadControlVector*)vector;
	TIMER renderTimer = TIMER();
	trigger *renderFrameTrigger = NULL;
	SCENE *currentScene = NULL;
	printf("RENDER -- Render Thread Starting\nRENDER -- Running On Core: %d\n", svcGetCurrentProcessorNumber());
	u64 lastNS = 0;
	while (rTCV->runThread) {
		//Tick The Main Timer
		renderTimer.update();
		//~~
		//Render Setup
		if (currentScene != rTCV->mainScene) {
			currentScene = rTCV->mainScene;
			renderTimer.clearTriggers();
			u64 frameTime = NS_TO_TICKS((1.0f / 60.0f) * 1000000000.0f);
			printf("RENDER -- FRAMETIME: %lu\n", frameTime);
			renderFrameTrigger = renderTimer.createTrigger(frameTime, 60);
		}
		if (renderFrameTrigger->count > 0) {
			renderFrameTrigger->reset();
			//Stub
		}
		//~~
	}
	printf("RENDER -- Thread Terminating\n");
}