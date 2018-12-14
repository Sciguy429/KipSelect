#pragma once

#include <string>

#define BCT_LIST_LENGTH 2

class bct {
public:
	void readBCT();
	void setBCT(int bctId, bool enabled);
private:
	std::string bctName[BCT_LIST_LENGTH];
	bool bctValue[BCT_LIST_LENGTH];
};