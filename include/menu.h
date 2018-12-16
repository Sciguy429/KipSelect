#pragma once

#include <switch.h>
#include <string>
#include <vector>

class MENU {
public:
	void init();
	void addTab(std::string tabName);
	void addOpt(int tabId, std::string optName);
	void reset();
	void handleInput(uint64_t kDown);
private:
	std::vector<std::vector<std::string>> menuMatrix;
};