#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "kip.h"

void KIP::scanKIP() {
	kipItems.clear();
	DIR* enabledKipDir;
	struct dirent* enabledKipEnt;
	enabledKipDir = opendir("/atmosphere/kips/");
	if (enabledKipDir == NULL) {
		if (mkdir("/atmosphere/kips/", 0700) == -1) {
			//TODO: Throw a proper error here (error.h/error.cpp)
		}
	}
	else {
		while ((enabledKipEnt = readdir(enabledKipDir))) {
			unsigned int pos = kipItems.size();
			kipItems.push_back(kipItem());
			kipItems[pos].name = enabledKipEnt->d_name;
			kipItems[pos].enabled = true;
		}
	}
	DIR* disabledKipDir;
	struct dirent* disabledKipEnt;
	disabledKipDir = opendir("/atmosphere/kips_disabled/");
	if (disabledKipDir == NULL) {
		if (mkdir("/atmosphere/kips_disabled/", 0700) == -1) {
			//TODO: Throw a proper error here (error.h/error.cpp)
		}
	}
	else {
		while ((disabledKipEnt = readdir(disabledKipDir))) {
			unsigned int pos = kipItems.size();
			kipItems.push_back(kipItem());
			kipItems[pos].name = disabledKipEnt->d_name;
			kipItems[pos].enabled = false;
		}
	}
}

void KIP::setKip(int kipId, bool enabled) {
	string name = kipName[kipId];
	string start = "/atmosphere/";
	string end = "/atmosphere/";
	if (enabled) {
		start.append("kips_disabled/");
		end.append("kips/");
	}
	else {
		start.append("kips/");
		end.append("kips_disabled/");
	}
	start.append(name);
	end.append(name);
	if (rename(start.c_str(), end.c_str()) != 0) {
		//TODO: Throw a proper error here (error.h/error.cpp)
	}
}

int KIP::getKipCount() {
	return kipCount;
}

string KIP::getKipName(int kipId) {
	return kipName[kipId];
}

bool KIP::getKipValue(int kipId) {
	return kipValue[kipId];
}