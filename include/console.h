#define LOG_LEVEL_INFO 0
#define LOG_LEVEL_WARNING 1
#define LOG_LEVEL_ERROR 2

using namespace std;

void initLocalConsole();

void initRemoteConsole();

void log(string str, int logLevel);