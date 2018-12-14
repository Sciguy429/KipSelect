#include <string>

#define KIP_LIST_LENGTH 32

using namespace std;

string kipName[KIP_LIST_LENGTH];
bool kipValue[KIP_LIST_LENGTH];

void scanForKip();

void setKip(int kipId, bool enabled);