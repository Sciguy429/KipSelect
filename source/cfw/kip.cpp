//Credit to hactool for the basic kip extraction code
//(https://github.com/SciresM/hactool/blob/master/kip.c)

#include <sstream>
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <algorithm>

#include "kip.h"
#include "error.h"

#define MAGIC_KIP1 0x3150494B

void KIP::scanKIP() {
	kipItems.clear();
	DIR* enabledKipDir;
	struct dirent* enabledKipEnt;
	enabledKipDir = opendir("sdmc:/atmosphere/kips/");
	if (enabledKipDir == NULL) {
		if (mkdir("sdmc:/atmosphere/kips/", 0700) == -1) {
			errorThrow(MKDIR_ERROR, "sdmc:/atmosphere/kips/");
		}
	}
	else {
		while ((enabledKipEnt = readdir(enabledKipDir))) {
			unsigned int pos = kipItems.size();
			kipItems.push_back(kipItem());
			kipItems[pos].name = enabledKipEnt->d_name;
			kipItems[pos].enabled = true;
			std::ostringstream ss;
			ss << "sdmc:/atmosphere/kips/" << enabledKipEnt->d_name;
			kipItems[pos].header = getKipHeader(ss.str().c_str());
		}
	}
	DIR* disabledKipDir;
	struct dirent* disabledKipEnt;
	disabledKipDir = opendir("sdmc:/atmosphere/kips_disabled/");
	if (disabledKipDir == NULL) {
		if (mkdir("sdmc:/atmosphere/kips_disabled/", 0700) == -1) {
			errorThrow(MKDIR_ERROR, "sdmc:/atmosphere/kips_disabled/");
		}
	}
	else {
		while ((disabledKipEnt = readdir(disabledKipDir))) {
			unsigned int pos = kipItems.size();
			kipItems.push_back(kipItem());
			kipItems[pos].name = disabledKipEnt->d_name;
			kipItems[pos].enabled = false;
			std::ostringstream ss;
			ss << "sdmc:/atmosphere/kips_disabled/" << disabledKipEnt->d_name;
			kipItems[pos].header = getKipHeader(ss.str().c_str());
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
		errorThrow(RENAME_ERROR, name.c_str());
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
	if (kipItems[kipId].header == NULL) {
		mnu.details.push_back(menuDetail());
		mnu.details[0].prefix = "Unknown Kip Format";
	}
	else {
		mnu.details.push_back(menuDetail());
		mnu.details[0].prefix = "Name: ";
		mnu.details[0].data = kipItems[kipId].header->name;
		mnu.details.push_back(menuDetail());
		mnu.details[1].prefix = "Title Id: ";
		char buf[18];
		sprintf(buf, "%lX", kipItems[kipId].header->title_id);
		mnu.details[1].data = buf;
	}
	return mnu;
}

kip1_header_t *KIP::getKipHeader(const char *path) {
	FILE *file = fopen(path, "r");
	kip1_header_t raw_header;
	fseeko(file, 0, SEEK_SET);
	if (fread(&raw_header, 1, sizeof(raw_header), file) != sizeof(raw_header)) {
		printf("Failed to read kip file %s\n", path);
		return NULL;
	}
	if (raw_header.magic != MAGIC_KIP1) {
		printf("Kip file %s magic dose not match expected magic (%X != %X)\n", path, raw_header.magic, MAGIC_KIP1);
		return NULL;
	}
	uint64_t size = 0x100 + raw_header.section_headers[0].compressed_size + raw_header.section_headers[1].compressed_size + raw_header.section_headers[2].compressed_size;
	kip1_header_t *header = (kip1_header_t*)malloc(size);
	if (header == NULL) {
		printf("Unabled to allocate required memory to header at address %p\n", (void*)header);
		return NULL;
	}
	fseeko(file, 0, SEEK_SET);
	if (fread(header, 1, size, file) != size) {
		printf("Failed to read kip file %s\n", path);
		return NULL;
	}
	fclose(file);
	return header;
}