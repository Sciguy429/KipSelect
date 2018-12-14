#pragma once

#include <string>

#define KIP_LIST_LENGTH 32

class KIP {
public:
	void scanForKip();
	void setKip(int kipId, bool enabled);
private:
	std::string kipName[KIP_LIST_LENGTH];
	bool kipValue[KIP_LIST_LENGTH];
};