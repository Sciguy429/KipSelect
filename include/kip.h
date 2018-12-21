#pragma once

#include <string>
#include <vector>

#include "menu.h"

typedef struct {
	std::string name;
	std::string md5;
	std::string version;
	std::string size;
	std::string description;
	bool enabled;
} kipItem;

class KIP {
public:
	void scanKIP();
	void setKIPItemEnabled(unsigned int kipId, bool enabled);
	bool getKIPItemEnabled(unsigned int kipId);
	unsigned int getKIPItemCount();
	menuItem getKIPMenuItem(unsigned int kipId);
private:
	std::vector<kipItem> kipItems;
};