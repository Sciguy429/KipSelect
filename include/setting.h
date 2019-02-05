#pragma once

#include <string>
#include <vector>

typedef struct {
	std::string key;
	std::string value;
} settingValue;

class SETTING {
public:
	void loadSetting(const char *path);
	void saveSetting(const char *path);
	std::string getValue(const char *key);
	void setValue(const char *key, const char *value);
private:
	std::vector<settingValue> settingValues;
};