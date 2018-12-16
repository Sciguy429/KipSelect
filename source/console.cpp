//DEPRACATED, Will rework later


#include <switch.h>
#include <stdio.h>
#include <string>

#include "console.h"

using namespace std;

void initLocalConsole() {
	consoleClear();
	printf(CONSOLE_ESC(4m) "Loading Kip Select...\n\n" CONSOLE_RESET);
}

void log(string str, int logLevel) {
	switch (logLevel) {
	case LOG_LEVEL_INFO:
		printf(CONSOLE_GREEN "INFO: ");
		break;
	case LOG_LEVEL_WARNING:
		printf(CONSOLE_YELLOW "WARNING: ");
		break;
	case LOG_LEVEL_ERROR:
		printf(CONSOLE_RED "ERROR: ");
		break;
	}
	printf(str.c_str());
	printf("\n");
}