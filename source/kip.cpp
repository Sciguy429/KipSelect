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

void KIP::setKIPItemEnabled(unsigned int kipId, bool enabled) {
	kipItems[kipId].enabled = enabled;
	std::string name = kipItems[kipId].name;
	std::string start = "/atmosphere/";
	std::string end = "/atmosphere/";
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

bool KIP::getKIPItemEnabled(unsigned int kipId) {
	return kipItems[kipId].enabled;
}

unsigned int KIP::getKIPCount() {
	return kipItems.size();
}

menuItem KIP::getKIPMenuItem(unsigned int kipId) {
	//TODO: Generate menuItem
	return menuItem();
}