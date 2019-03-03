#pragma once

#include <switch.h>
#include <vector>

#define NS_TO_TICKS(ns) {armNsToTicks(ns)}
#define TICKS_TO_NS(ticks) {armTicksToNs(ticks)}

typedef struct {
	u64 interval;
	u64 maxCount;
	u64 lastTick;
	u64 count;
	void reset() {
		lastTick = armGetSystemTick();
		count = 0;
	}
} trigger;

class TIMER {
public:
	trigger *createTrigger(u64 interval, u64 maxCount);
	void clearTriggers();
	void update();
	~TIMER();
private:
	std::vector<trigger*> triggers;
};