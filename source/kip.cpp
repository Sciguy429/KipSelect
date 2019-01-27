#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "kip.h"
#include "error.h"

void KIP::scanKIP() {
	kipItems.clear();
	DIR* enabledKipDir;
	struct dirent* enabledKipEnt;
	enabledKipDir = opendir("sdmc:/atmosphere/kips/");
	if (enabledKipDir == NULL) {
		if (mkdir("sdmc:/atmosphere/kips/", 0700) == -1) {
			errorThrow(0, "sdmc:/atmosphere/kips/");
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
	disabledKipDir = opendir("sdmc:/atmosphere/kips_disabled/");
	if (disabledKipDir == NULL) {
		if (mkdir("sdmc:/atmosphere/kips_disabled/", 0700) == -1) {
			errorThrow(0, "sdmc:/atmosphere/kips_disabled/");
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
	std::string start = "sdmc:/atmosphere/";
	std::string end = "sdmc:/atmosphere/";
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
		errorThrow(1, name.c_str());
	}
}

bool KIP::getKIPItemEnabled(unsigned int kipId) {
	return kipItems[kipId].enabled;
}

unsigned int KIP::getKIPItemCount() {
	return kipItems.size();
}

menuItem KIP::getKIPMenuItem(unsigned int kipId) {
	menuItem mnu;
	mnu.name = kipItems[kipId].name;
	mnu.status = kipItems[kipId].enabled;
	//mnu.details.push_back(menuDetail());
	//mnu.details[0].prefix = "Md5: ";
	//mnu.details[0].data = kipItems[kipId].md5;
	//mnu.details.push_back(menuDetail());
	//mnu.details[1].prefix = "Version: ";
	//mnu.details[1].data = kipItems[kipId].version;
	//mnu.details.push_back(menuDetail());
	//mnu.details[2].prefix = "Size: ";
	//mnu.details[2].data = kipItems[kipId].size;
	//mnu.details[2].suffix = "KB";
	//mnu.details.push_back(menuDetail());
	//mnu.details[3].prefix = "Discription:\n";
	//mnu.details[3].data = "This is a test of a discription";
	return mnu;
}