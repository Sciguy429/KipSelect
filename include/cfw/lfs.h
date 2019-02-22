#pragma once

#include <string>
#include <vector>

typedef struct {
	std::string titleId;
	std::string titleName;
	std::string titlePublisher;
	std::string titleRegion;
	std::string titleLanguages;
} nswTitle;

typedef struct {
	std::string titleId;
	std::string titleName;
	std::string titleDescription;
} sysTitle;

typedef struct {
	std::string name;
	std::string titleId;
	std::string discription;
	bool enabled;
} lfsItem;

class LFS {
public:
	void updateLFSDatabase();
	void parseLFSDatabase();
	void parseSysDatabase();
	void scanLFS();
	void setLFSItemEnabled(unsigned int lfsId, bool enabled);
	bool getLFSItemEnabled(unsigned int lfsId);
	unsigned int getLFSCount();
	//menuItem getLFSMenuItem(unsigned int lfsId);
private:
	std::vector<nswTitle> nswTitles;
	std::vector<sysTitle> sysTitles;
	std::vector<lfsItem> lfsItems;
};