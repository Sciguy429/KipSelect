#include <fstream>
#include <sstream>

#include "ini.h"
#include "error.h"

void INI::setValue(const char *targetKey, const char *value) {
	std::ifstream iniFileIn(iniPath);
	std::ostringstream outputString;
	int pos = getLocation(targetKey);
	if (pos != -1) {
		std::string line;
		for (int i = 0; i < pos; i++) {
			std::getline(iniFileIn, line, '\n');
			if (i < pos - 1) {
				outputString << line << '\n';
			}
		}
		std::string::size_type seperator = line.find_first_of('=');
		if (seperator != std::string::npos) {
			std::string key = removeSpaces(line.substr(0, seperator));
			if (!key.empty()) {
				if (key == targetKey) {
					outputString << line.substr(0, seperator + 1);
					for (unsigned int i = seperator + 1; i < line.length(); i++) {
						if (line.at(i) == ' ') {
							outputString << line.at(i);
						}
						else {
							outputString << value << "\r\n";
							break;
						}
					}
				}
			}
		}
		while (std::getline(iniFileIn, line, '\n')) {
			outputString << line << '\n';
		}
		iniFileIn.close();
		std::ofstream iniFileOut(iniPath);
		if (iniFileOut.is_open()) {
			iniFileOut << outputString;
			iniFileOut.close();
		}
		else {
			errorThrow(OFSTREAM_ERROR, iniPath);
			return;
		}
	}
}

std::string INI::getValue(const char *targetKey) {
	std::ifstream iniFileIn(iniPath);
	int pos = getLocation(targetKey);
	if (pos != -1) {
		std::string line;
		for (int i = 0; i < pos; i++) {
			std::getline(iniFileIn, line, '\n');
		}
		std::string::size_type seperator = line.find_first_of('=');
		if (seperator != std::string::npos) {
			std::string key = removeSpaces(line.substr(0, seperator));
			std::string value = removeSpaces(line.substr(seperator + 1));
			if (!key.empty() && !value.empty()) {
				if (key == targetKey) {
					iniFileIn.close();
					return value;
				}
			}
		}
	}
	iniFileIn.close();
	return std::string();
}

INI::INI(const char *path) {
	iniPath = path;
}

int INI::getLocation(const char *targetKey) {
	std::ifstream iniFileIn(iniPath);
	std::string line;
	unsigned int pos = 0;
	while (std::getline(iniFileIn, line, '\n')) {
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
							iniFileIn.close();
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
	iniFileIn.close();
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