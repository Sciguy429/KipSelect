#include <math.h>

#include "utils/timer.h"

trigger *TIMER::createTrigger(u64 interval, u64 maxCount) {
	unsigned int pos = triggers.size();
	triggers.push_back(trigger());
	triggers[pos].interval = interval;
	triggers[pos].maxCount = maxCount;
	triggers[pos].reset();
	return &triggers[pos];
}

void TIMER::clearTriggers() {
	triggers.clear();
}

void TIMER::update() {
	for (std::size_t i = 0; i < triggers.size(); i++) {
		trigger *t = &triggers[i];
		u64 curTick = armGetSystemTick();
		if (curTick > t->interval + t->lastTick) {
			u64 diffTick = curTick - t->lastTick;
			u64 incCount = floor((float)diffTick / (float)t->interval);
			incCount = incCount + t->count;
			if (incCount > t->maxCount) {
				t->count = t->maxCount;
				continue;
			}
			t->count = incCount;
		}
	}
}