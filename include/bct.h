#pragma once

#include <string>

#define BCT_LIST_LENGTH 2

class BCT {
public:
	void readBCT();
	void setBCT(int bctId, bool enabled);
	int getBCTCount();
	std::string getBCTName(int bctId);
	bool getBCTValue(int bctId);
private:
	std::string bctName[BCT_LIST_LENGTH] = {"debugmode", "debugmode_user"};
	bool bctValue[BCT_LIST_LENGTH];
};