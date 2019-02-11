#pragma once

#include <string>

class INI {
public:
	bool setValue(const char *targetKey, const char *value);
	std::string getValue(bool *valid, const char *targetKey);
	INI(const char *path);
private:
	int getLocation(const char *targetKey);
	std::string removeSpaces(std::string str);
	const char *iniPath;
};