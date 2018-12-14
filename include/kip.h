#pragma once

#include <string>

#define KIP_LIST_LENGTH 32

class KIP {
public:
	void scanForKip();
	void setKip(int kipId, bool enabled);
	int getKipCount();
	std::string getKipName(int kipId);
	bool getKipValue(int kipId);
private:
	std::string kipName[KIP_LIST_LENGTH];
	bool kipValue[KIP_LIST_LENGTH];
	int kipCount = 0;
};