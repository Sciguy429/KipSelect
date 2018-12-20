#include <sstream>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "lfs.h"

void LFS::scanLFS() {
	lfsItems.clear();
	DIR* lfsDir;
	struct dirent* lfsEnt;
	lfsDir = opendir("/atmosphere/titles/");
	if (lfsDir == NULL) {
		if (mkdir("/atmosphere/titles/", 0700) == -1) {
			//TODO: Throw a proper error here
		}
	}
	else {
		while ((lfsEnt = readdir(lfsDir))) {
			unsigned int pos = lfsItems.size();
			lfsItems.push_back(lfsItem());
			lfsItems[pos].titleId = lfsEnt->d_name;
			printf("LFS FOUND: %s\n", lfsEnt->d_name);
			std::ostringstream flagsPath;
			flagsPath << "/atmosphere/titles/" << lfsEnt->d_name;
			struct stat info;
			stat(flagsPath.str().c_str(), &info);
			if (info.st_mode & S_IFDIR) {
				flagsPath << "/disabled.flag";
				if (stat(flagsPath.str().c_str(), &info) == 0) {
					lfsItems[pos].titleEnabled = false;
				}
				else {
					lfsItems[pos].titleEnabled = true;
				}
			}
			else {
				lfsItems[pos].titleEnabled = true;
				if (mkdir(flagsPath.str().c_str(), 0700) == -1) {
					//TODO: Throw a proper error here
				}
			}
			printf("---%s\n", lfsItems[pos].titleEnabled ? "Enabled" : "Disabled");
		}
	}
}

unsigned int LFS::getLFSCount() {
	return lfsItems.size();
}

menuItem LFS::getLFSMenuItem(unsigned int lfsId) {
	//stub
	return menuItem();
}