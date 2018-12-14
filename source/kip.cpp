#include <switch.h>
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "kip.h"
#include "console.h"

using namespace std;

void KIP::scanForKip() {
	int kipCount = 0;
	DIR* enabledKipDir;
	struct dirent* enabledKipEnt;
	enabledKipDir = opendir("/atmosphere/kips/");
	if (enabledKipDir == NULL) {
		if (mkdir("/atmosphere/kips/", 0700) == -1) {
			//printError(0, "/atmosphere/kips/");
			log("Unable To Make Dirrectory /atmopshere/kips/", LOG_LEVEL_ERROR);
		}
	}
	else {
		while ((enabledKipEnt = readdir(enabledKipDir))) {
			kipName[kipCount] = enabledKipEnt->d_name;
			kipValue[kipCount] = true;
			kipCount++;
			if (kipCount == KIP_LIST_LENGTH) {
				kipCount = 0; //Set the kip count back to 0 to prevent a crash screen from showing
				//printError(2, "");
				log("More Than 32 Kips Detected", LOG_LEVEL_ERROR);
				return;
			}
		}
	}
	DIR* disabledKipDir;
	struct dirent* disabledKipEnt;
	disabledKipDir = opendir("/atmosphere/kips_disabled/");
	if (disabledKipDir == NULL) {
		if (mkdir("/atmosphere/kips_disabled/", 0700) == -1) {
			//printError(0, "/atmosphere/kips_disabled/");
			log("Unable To Make Dirrectory /atmosphere/kips_disabled/", LOG_LEVEL_ERROR);
		}
	}
	else {
		while ((disabledKipEnt = readdir(disabledKipDir))) {
			kipName[kipCount] = disabledKipEnt->d_name;
			kipValue[kipCount] = false;
			kipCount++;
			if (kipCount == KIP_LIST_LENGTH) {
				kipCount = 0; //Set the kip count back to 0 to prevent a crash screen from showing
				//printError(2, "");
				log("More Than 32 Kips Detected", LOG_LEVEL_ERROR);
				return;
			}
		}
	}
	if (kipCount == 0) {
		//printError(1, "");
		log("No Kips Found", LOG_LEVEL_ERROR);
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
		//printError(3, name);
		log("Unable To Move Kip Between Dirrectories", LOG_LEVEL_ERROR);
	}
}