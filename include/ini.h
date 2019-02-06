#pragma once

#include <string>
#include <vector>

typedef struct {
	std::string key;
	std::string data;
} iniValue;

class INI {
public:
	void setValue(const char *key, const char *value);
	std::string getValue(const char *key);
	void saveINI(const char *path);
	void loadINI(const char *path);
private:
	std::vector<iniValue> iniValues;
};