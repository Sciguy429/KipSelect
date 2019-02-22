#pragma once

#include <string>
#include <vector>

typedef struct {
	std::string name;
	std::string target;
	std::string description;
	bool enabled;
} bctItem;

class BCT {
public:
	void scanBCT();
	void setBCTItemEnabled(unsigned int bctId, bool enabled);
	bool getBCTItemEnabled(unsigned int bctId);
	unsigned int getBCTItemCount();
	//menuItem getBCTMenuItem(unsigned int bctId);
private:
	std::vector<bctItem> bctItems;
	std::string bctNames[3] = {"Debug Mode", "Debug Mode User", "No Gamecard"};
	std::string bctTargets[3] = {"debugmode = ", "debugmode_user = ", "nogc = "};
	std::string bctDiscriptions[3] = {
		"Sets the debugability of processes console wide. As of Atmosphere 0.8.2 this is enabled by default and should most likely never need to be disabled.",
		"Informs userland that debugmode is active. Don't enable this unless you know what you are doing.",
		"Enables or disables the gamecard slot. This is typically used to prevent the gamecard firmware from updateing. By default this option is commented out in BCT.ini as Atmosphere will automatically apply these patches when necessary. If you would like this tool to actualy change this value you must first manualy edit BCT.ini and remove this comment, otherwise toggling this will do nothing."
	};
};