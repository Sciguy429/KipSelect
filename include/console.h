#pragma once

#include <sstream>

#define SSTR(x) static_cast< std::ostringstream & > (( std::ostringstream() << std::dec << x )).str()

#define LOG_LEVEL_INFO 0
#define LOG_LEVEL_WARNING 1
#define LOG_LEVEL_ERROR 2

void initLocalConsole();

void log(std::string str, int logLevel);
