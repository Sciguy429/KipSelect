#pragma once

#define LOG_LEVEL_INFO 0
#define LOG_LEVEL_WARNING 1
#define LOG_LEVEL_ERROR 2

void initLocalConsole();

void initRemoteConsole();

void log(std::string str, int logLevel);