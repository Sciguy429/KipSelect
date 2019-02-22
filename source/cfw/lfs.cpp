#include <sstream>
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <libxml2/libxml/xmlmemory.h>
#include <libxml2/libxml/parser.h>
#include <algorithm>

#include "cfw/lfs.h"
#include "error.h"
#include "utils/net.h"

struct nswFindId : std::unary_function<nswTitle, bool> {
	std::string id;
	nswFindId(std::string id) :id(id) { }
	bool operator()(nswTitle const& m) const {
		return m.titleId == id;
	}
};

struct sysFindId : std::unary_function<sysTitle, bool> {
	std::string id;
	sysFindId(std::string id) :id(id) { }
	bool operator()(sysTitle const& m) const {
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
			errorThrow(RENAME_ERROR, "sdmc:/NEW.NSWreleases.xml");
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
		errorThrow(XML_ERROR, "NSWreleases.xml failed to parse");
		return;
	}
	nswCur = xmlDocGetRootElement(nswDoc);
	if (nswCur == NULL) {
		errorThrow(XML_ERROR, "NSWreleases.xml is empty");
		return;
	}
	if (xmlStrcmp(nswCur->name, (const xmlChar *)"releases")) {
		errorThrow(XML_ERROR, "NSWreleases.xml is the wrong type, root node != releases");
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

void LFS::parseSysDatabase() {
	xmlDocPtr sysDoc;
	xmlNodePtr sysCur;
	sysDoc = xmlParseFile("romfs:/data/SystemTitles.xml");
	if (sysDoc == NULL) {
		errorThrow(XML_ERROR, "SystemTitles.xml failed to parse");
		return;
	}
	sysCur = xmlDocGetRootElement(sysDoc);
	if (sysCur == NULL) {
		errorThrow(XML_ERROR, "SystemTitles.xml is empty");
		return;
	}
	if (xmlStrcmp(sysCur->name, (const xmlChar *)"titles")) {
		errorThrow(XML_ERROR, "SystemTitles.xml is the wrong type, root node != titles");
		xmlFreeDoc(sysDoc);
		return;
	}
	sysCur = sysCur->xmlChildrenNode;
	unsigned int sysCount = 0;
	while (sysCur != NULL) {
		if ((!xmlStrcmp(sysCur->name, (const xmlChar *)"title"))) {
			sysTitles.push_back(sysTitle());
			xmlChar *releaseKey;
			xmlNodePtr releaseCur = sysCur->xmlChildrenNode;
			while (releaseCur != NULL) {
				if ((!xmlStrcmp(releaseCur->name, (const xmlChar *)"name"))) { //Title Id
					releaseKey = xmlNodeListGetString(sysDoc, releaseCur->xmlChildrenNode, 1);
					sysTitles[sysCount].titleName = reinterpret_cast<const char*>(releaseKey);
					xmlFree(releaseKey);
				}
				else if ((!xmlStrcmp(releaseCur->name, (const xmlChar *)"titleid"))) { //Title Name
					releaseKey = xmlNodeListGetString(sysDoc, releaseCur->xmlChildrenNode, 1);
					sysTitles[sysCount].titleId = reinterpret_cast<const char*>(releaseKey);
					xmlFree(releaseKey);
				}
				else if ((!xmlStrcmp(releaseCur->name, (const xmlChar *)"description"))) { //Title Description
					releaseKey = xmlNodeListGetString(sysDoc, releaseCur->xmlChildrenNode, 1);
					sysTitles[sysCount].titleDescription = reinterpret_cast<const char*>(releaseKey);
					xmlFree(releaseKey);
				}
				releaseCur = releaseCur->next;
			}
			sysCount++;
		}
		sysCur = sysCur->next;
	}
	printf("Parsed %d system titles from file romfs:/data/SystemTitles.xml\n", sysCount);
	xmlFreeDoc(sysDoc);
}

void LFS::scanLFS() {
	lfsItems.clear();
	DIR* lfsDir;
	struct dirent* lfsEnt;
	lfsDir = opendir("sdmc:/atmosphere/titles/");
	if (lfsDir == NULL) {
		if (mkdir("sdmc:/atmosphere/titles/", 0700) == -1) {
			errorThrow(MKDIR_ERROR, "sdmc:/atmosphere/titles/");
		}
	}
	else {
		while ((lfsEnt = readdir(lfsDir))) {
			unsigned int pos = lfsItems.size();
			lfsItems.push_back(lfsItem());
			lfsItems[pos].titleId = lfsEnt->d_name;
			std::ostringstream flagsPath;
			flagsPath << "sdmc:/atmosphere/titles/" << lfsEnt->d_name << "/flags";
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
					errorThrow(MKDIR_ERROR, flagsPath.str().c_str());
				}
			}
		}
	}
}

void LFS::setLFSItemEnabled(unsigned int lfsId, bool enabled) {
	lfsItems[lfsId].enabled = enabled;
	std::ostringstream flagsPath;
	flagsPath << "sdmc:/atmosphere/titles/" << lfsItems[lfsId].titleId << "/flags";
	struct stat info;
	stat(flagsPath.str().c_str(), &info);
	if (!(info.st_mode & S_IFDIR)) {
		if (mkdir(flagsPath.str().c_str(), 0700) == -1) {
			errorThrow(MKDIR_ERROR, flagsPath.str().c_str());
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
			errorThrow(OFSTREAM_ERROR, flagsPath.str().c_str());
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
	std::vector<sysTitle>::iterator sysItr = std::find_if(sysTitles.begin(), sysTitles.end(), sysFindId(str));
	if (sysItr != sysTitles.end()) {
		mnu.name = sysItr->titleName;
		mnu.details.push_back(menuDetail());
		mnu.details[0].prefix = "Title Id: ";
		mnu.details[0].data = sysItr->titleId;
		mnu.details.push_back(menuDetail());
		mnu.details[1].prefix = "Description: ";
		mnu.details[1].data = sysItr->titleDescription;
	}
	else {
		std::vector<nswTitle>::iterator nswItr = std::find_if(nswTitles.begin(), nswTitles.end(), nswFindId(str));
		if (nswItr != nswTitles.end()) {
			mnu.name = nswItr->titleName;
			mnu.details.push_back(menuDetail());
			mnu.details[0].prefix = "Title Id: ";
			mnu.details[0].data = nswItr->titleId;
			mnu.details.push_back(menuDetail());
			mnu.details[1].prefix = "Title Publisher: ";
			mnu.details[1].data = nswItr->titlePublisher;
			mnu.details.push_back(menuDetail());
			mnu.details[2].prefix = "Title Region: ";
			mnu.details[2].data = nswItr->titleRegion;
			mnu.details.push_back(menuDetail());
			mnu.details[3].prefix = "Title Languages: ";
			mnu.details[3].data = nswItr->titleLanguages;
		}
		else {
			mnu.name = lfsItems[lfsId].titleId;
			mnu.details.push_back(menuDetail());
			mnu.details[0].prefix = "Futher Title Infomation Unknown";
		}
	}
	return mnu;
}