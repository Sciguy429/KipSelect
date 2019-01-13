#include <sstream>
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <libxml2/libxml/xmlmemory.h>
#include <libxml2/libxml/parser.h>
#include <algorithm>

#include "lfs.h"
#include "error.h"
#include "net.h"

struct find_id : std::unary_function<nswTitle, bool> {
	std::string id;
	find_id(std::string id) :id(id) { }
	bool operator()(nswTitle const& m) const {
		return m.titleId == id;
	}
};

std::ifstream::pos_type fileSize(const char* filename) {
	std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
	return in.tellg();
}

void LFS::updateLFSDatabase() {
	remove("sdmc:/NEW.NSWreleases.xml");
	netDownloadFile("http://nswdb.com/xml.php", "sdmc:/NEW.NSWreleases.xml");
	if (fileSize("sdmc:/NEW.NSWreleases.xml") > 0) {
		remove("sdmc:/NSWreleases.xml");
		if (rename("sdmc:/NEW.NSWreleases.xml", "sdmc:/NSWreleases.xml") != 0) {
			errorThrow(1, "sdmc:/NEW.NSWreleases.xml");
		}
	}
	else {
		remove("sdmc:/NEW.NSWreleases.xml");
	}
}

void LFS::parseLFSDatabase() {
	std::string nswLocation;
	struct stat info;
	if (stat("sdmc:/NSWreleases.xml", &info) == 0) {
		nswLocation = "sdmc:/NSWreleases.xml";
	}
	else {
		nswLocation = "romfs:/data/NSWreleases.xml";
	}
	xmlDocPtr nswDoc;
	xmlNodePtr nswCur;
	nswDoc = xmlParseFile(nswLocation.c_str());
	if (nswDoc == NULL) {
		errorThrow(5, "Document failed to parse");
		return;
	}
	nswCur = xmlDocGetRootElement(nswDoc);
	if (nswCur == NULL) {
		errorThrow(5, "Document is empty");
		return;
	}
	if (xmlStrcmp(nswCur->name, (const xmlChar *)"releases")) {
		errorThrow(5, "Document of the wrong type, root node != releases");
		xmlFreeDoc(nswDoc);
		return;
	}
	nswCur = nswCur->xmlChildrenNode;
	unsigned int nswCount = 0;
	while (nswCur != NULL) {
		if ((!xmlStrcmp(nswCur->name, (const xmlChar *)"release"))) {
			nswTitles.push_back(nswTitle());
			xmlChar *releaseKey;
			xmlNodePtr releaseCur = nswCur->xmlChildrenNode;
			while (releaseCur != NULL) {
				if ((!xmlStrcmp(releaseCur->name, (const xmlChar *)"name"))) { //Title Name
					releaseKey = xmlNodeListGetString(nswDoc, releaseCur->xmlChildrenNode, 1);
					nswTitles[nswCount].titleName = reinterpret_cast<const char*>(releaseKey);
					xmlFree(releaseKey);
				}
				else if ((!xmlStrcmp(releaseCur->name, (const xmlChar *)"titleid"))) { //Title Id
					releaseKey = xmlNodeListGetString(nswDoc, releaseCur->xmlChildrenNode, 1);
					nswTitles[nswCount].titleId = reinterpret_cast<const char*>(releaseKey);
					xmlFree(releaseKey);
				}
				else if ((!xmlStrcmp(releaseCur->name, (const xmlChar *)"publisher"))) { //Title Publisher
					releaseKey = xmlNodeListGetString(nswDoc, releaseCur->xmlChildrenNode, 1);
					nswTitles[nswCount].titlePublisher = reinterpret_cast<const char*>(releaseKey);
					xmlFree(releaseKey);
				}
				else if ((!xmlStrcmp(releaseCur->name, (const xmlChar *)"region"))) { //Title Region
					releaseKey = xmlNodeListGetString(nswDoc, releaseCur->xmlChildrenNode, 1);
					nswTitles[nswCount].titleRegion = reinterpret_cast<const char*>(releaseKey);
					xmlFree(releaseKey);
				}
				else if ((!xmlStrcmp(releaseCur->name, (const xmlChar *)"languages"))) { //Title Languages
					releaseKey = xmlNodeListGetString(nswDoc, releaseCur->xmlChildrenNode, 1);
					nswTitles[nswCount].titleLanguages = reinterpret_cast<const char*>(releaseKey);
					xmlFree(releaseKey);
				}
				releaseCur = releaseCur->next;
			}
			nswCount++;
		}
		nswCur = nswCur->next;
	}
	printf("Parsed %d releases from file %s\n", nswCount, nswLocation.c_str());
	xmlFreeDoc(nswDoc);
}

void LFS::scanLFS() {
	lfsItems.clear();
	DIR* lfsDir;
	struct dirent* lfsEnt;
	lfsDir = opendir("/atmosphere/titles/");
	if (lfsDir == NULL) {
		if (mkdir("/atmosphere/titles/", 0700) == -1) {
			errorThrow(0, "/atmosphere/titles/");
		}
	}
	else {
		while ((lfsEnt = readdir(lfsDir))) {
			unsigned int pos = lfsItems.size();
			lfsItems.push_back(lfsItem());
			lfsItems[pos].titleId = lfsEnt->d_name;
			std::ostringstream flagsPath;
			flagsPath << "/atmosphere/titles/" << lfsEnt->d_name << "/flags";
			struct stat info;
			stat(flagsPath.str().c_str(), &info);
			if (info.st_mode & S_IFDIR) {
				flagsPath << "/fsmitm_disable.flag";
				if (stat(flagsPath.str().c_str(), &info) == 0) {
					lfsItems[pos].enabled = false;
				}
				else {
					lfsItems[pos].enabled = true;
				}
			}
			else {
				lfsItems[pos].enabled = true;
				if (mkdir(flagsPath.str().c_str(), 0700) == -1) {
					errorThrow(0, flagsPath.str().c_str());
				}
			}
		}
	}
}

void LFS::setLFSItemEnabled(unsigned int lfsId, bool enabled) {
	lfsItems[lfsId].enabled = enabled;
	std::ostringstream flagsPath;
	flagsPath << "/atmosphere/titles/" << lfsItems[lfsId].titleId << "/flags";
	struct stat info;
	stat(flagsPath.str().c_str(), &info);
	if (!(info.st_mode & S_IFDIR)) {
		if (mkdir(flagsPath.str().c_str(), 0700) == -1) {
			errorThrow(0, flagsPath.str().c_str());
		}
	}
	flagsPath << "/fsmitm_disable.flag";
	if (enabled) {
		remove(flagsPath.str().c_str());
	}
	else {
		std::ofstream flag(flagsPath.str().c_str());
		if (flag.is_open()) {
			flag.close();
		}
		else {
			errorThrow(2, flagsPath.str().c_str());
		}
	}
}

bool LFS::getLFSItemEnabled(unsigned int lfsId) {
	return lfsItems[lfsId].enabled;
}

unsigned int LFS::getLFSCount() {
	return lfsItems.size();
}

menuItem LFS::getLFSMenuItem(unsigned int lfsId) {
	menuItem mnu;
	mnu.status = lfsItems[lfsId].enabled;
	std::string str = lfsItems[lfsId].titleId;
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);
	std::vector<nswTitle>::iterator itr = std::find_if(nswTitles.begin(), nswTitles.end(), find_id(str));
	if (itr != nswTitles.end()) {
		mnu.name = itr->titleName;
		mnu.details.push_back(menuDetail());
		mnu.details[0].prefix = "Title Id: ";
		mnu.details[0].data = itr->titleId;
		mnu.details.push_back(menuDetail());
		mnu.details[1].prefix = "Title Publisher: ";
		mnu.details[1].data = itr->titlePublisher;
		mnu.details.push_back(menuDetail());
		mnu.details[2].prefix = "Title Region: ";
		mnu.details[2].data = itr->titleRegion;
		mnu.details.push_back(menuDetail());
		mnu.details[3].prefix = "Title Languages: ";
		mnu.details[3].data = itr->titleLanguages;
	}
	else {
		mnu.name = lfsItems[lfsId].titleId;
		mnu.details.push_back(menuDetail());
		mnu.details[0].prefix = "Futher Title Infomation Unknown";
	}
	return mnu;
}