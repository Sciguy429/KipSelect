#include <fstream>
#include <algorithm>

#include "ini.h"
#include "error.h"

struct valueFindKey : std::unary_function<iniValue, bool> {
	std::string key;
	valueFindKey(std::string key) :key(key) { }
	bool operator()(iniValue const& m) const {
		return m.key == key;
	}
};

void INI::setValue(const char *key, const char *value) {
	size_t size = iniValues.size();
	iniValues.push_back(iniValue());
	iniValues[size].key = key;
	iniValues[size].data = value;
}

std::string INI::getValue(const char *key) {
	std::vector<iniValue>::iterator iniItr = std::find_if(iniValues.begin(), iniValues.end(), valueFindKey(key));
	if (iniItr != iniValues.end()) {
		return iniItr->data;
	}
	return NULL;
}

void INI::saveINI(const char *path) {
	std::ofstream iniFile(path);
	if (iniFile.is_open()) {
		for (unsigned int i = 0; i < iniValues.size(); i++) {
			iniFile << iniValues[i].key << '=' << '"' << iniValues[i].data << '"' << '\n';
		}
		iniFile.close();
	}
	else {
		errorThrow(OFSTREAM_ERROR, path);
		return;
	}
}

void INI::loadINI(const char *path) {
	iniValues.clear();
	std::ifstream iniFile(path);
	while (iniFile) {
		std::string line;
		std::getline(iniFile, line, '\n');
		if (line[0] != '#' && line.length() > 0) {
			std::string::size_type seperator = line.find_first_of('=');
			if (seperator != std::string::npos) {
				std::string key = line.substr(0, seperator);
				std::string value = line.substr(seperator);
				std::string::size_type pos1 = value.find_first_of('"');
				std::string::size_type pos2 = value.find_last_of('"');
				if (pos1 != std::string::npos && pos2 != std::string::npos && pos2 > pos1) {
					value = value.substr(pos1 + 1, pos2 - pos1 - 1);
					setValue(key.c_str(), value.c_str());
				}
				else {
					errorThrow(INI_PARSE_FAIL, line.c_str());
					return;
				}
			}
			else {
				errorThrow(INI_PARSE_FAIL, line.c_str());
				return;
			}
		}
	}
	iniFile.close();
}
