#include <fstream>

#include "ini.h"
#include "error.h"

void INI::setValue(const char *targetKey, const char *value) {
	//~~~Stub~~~
	//Will eventualy set a value at key in the current file.
	//Needs to do everything it can to keep file layout the same.
}

std::string INI::getValue(const char *targetKey) {
	std::ifstream iniFile(iniPath);
	int pos = getLocation(targetKey);
	if (pos != -1) {
		std::string line;
		for (int i = 0; i < pos; i++) {
			std::getline(iniFile, line, '\n');
		}
		std::string::size_type seperator = line.find_first_of('=');
		if (seperator != std::string::npos) {
			std::string key = removeSpaces(line.substr(0, seperator));
			std::string value = removeSpaces(line.substr(seperator + 1));
			if (!key.empty() && !value.empty()) {
				if (key == targetKey) {
					iniFile.close();
					return value;
				}
			}
		}
	}
	iniFile.close();
	return std::string();
}

INI::INI(const char *path) {
	iniPath = path;
}

int INI::getLocation(const char *targetKey) {
	std::ifstream iniFile(iniPath);
	std::string line;
	unsigned int pos = 0;
	while (std::getline(iniFile, line, '\n')) {
		pos++;
		if (line.at(line.length() - 1) == '\r') {
			if (line.length() > 1) {
				line = line.substr(0, line.length() - 1);
			}
			else {
				line.clear();
			}
		}
		if (!line.empty()) {
			if (line.at(0) != ';') {
				std::string::size_type seperator = line.find_first_of('=');
				if (seperator != std::string::npos) {
					std::string key = removeSpaces(line.substr(0, seperator));
					std::string value = removeSpaces(line.substr(seperator + 1));
					if (!key.empty() && !value.empty()) {
						if (key == targetKey) {
							iniFile.close();
							return pos;
						}
					}
					else {
						printf("Empty key/value in file: %s at line: %d\n", iniPath, pos);
					}
				}
				else {
					printf("Unparseable line in file: %s at line: %d\n", iniPath, pos);
				}
			}
		}
	}
	iniFile.close();
	return -1;
}

std::string INI::removeSpaces(std::string str) {
	std::string::size_type pos = str.find_first_of(' ');
	if (pos != std::string::npos) {
		unsigned int start = 0;
		for (unsigned int i = 0; i < str.length(); i++) {
			if (str.at(i) == ' ') {
				start = i + 1;
			}
			else {
				break;
			}
		}
		unsigned int end = str.length();
		for (unsigned int i = start; i < str.length(); i++) {
			if (str.at(i) != ' ') {
				end = i + 1;
			}
		}
		return str.substr(start, end);
	}
	return str;
}