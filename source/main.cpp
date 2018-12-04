#include <switch.h>
#include <string>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

using namespace std;

string kips[32];
bool kipsEnabled[32];
bool run = true;
int kipSelected = 0;
int kipsCount = 0;
u64 kDown;

void updateInputs() {
  hidScanInput();
  kDown = hidKeysDown(CONTROLLER_P1_AUTO);
  if (kDown & KEY_PLUS) run = false;
}

void printError(int errorCode, string extra) {
  printf(CONSOLE_ESC(2J) CONSOLE_RED "An Error Has Occured! (Error Code: %d) Press '+' To Exit Back To HB-Menu\n\n", errorCode);
  switch (errorCode) {
    case 0:
    printf("Unable To Make Dirrectory: %s", extra.c_str());
    break;
    case 1:
    printf("No Kips Found!\nDid You Install Any?");
    break;
    case 2:
    printf("More Than 32 Kips Found!");
    break;
    case 3:
    printf("File Moved Failed!\nOffending Kip: %s\n\n\nThis Is Typicly Caused By A Kip Being Present In kips and kips_disabled\nAt The Same Time, Check These Folders First", extra.c_str());
    break;
    default:
    printf("UKNOWN ERROR\n(You're In DEEP Trouble If This Shows Up Lol :P)");
    break;
  }
  while (run) {
    consoleUpdate(NULL);
    updateInputs();
  }
}

void scanForKip() {
  kipsCount = 0;
  DIR* enabledKipDir;
  struct dirent* enabledKipEnt;
  enabledKipDir = opendir("/atmosphere/kips/");
  if (enabledKipDir == NULL) {
    if (mkdir("/atmosphere/kips/", 0700) == -1) {
      printError(0, "/atmosphere/kips/");
    }
  }
  else {
    while ((enabledKipEnt = readdir(enabledKipDir))) {
      kips[kipsCount] = enabledKipEnt->d_name;
      kipsEnabled[kipsCount] = true;
      kipsCount++;
      if (kipsCount == 32) {
        kipsCount = 0; //Set the kip count back to 0 to prevent a crash screen from showing
        printError(2, "");
      }
    }
  }
  DIR* disabledKipDir;
  struct dirent* disabledKipEnt;
  disabledKipDir = opendir("/atmosphere/kips_disabled/");
  if (disabledKipDir == NULL) {
    if (mkdir("/atmosphere/kips_disabled/", 0700) == -1) {
      printError(0, "/atmosphere/kips_disabled/");
    }
  }
  else {
    while ((disabledKipEnt = readdir(disabledKipDir))) {
      kips[kipsCount] = disabledKipEnt->d_name;
      kipsEnabled[kipsCount] = false;
      kipsCount++;
      if (kipsCount == 32) {
        kipsCount = 0; //Set the kip count back to 0 to prevent a crash screen from showing
        printError(2, "");
      }
    }
  }
  if (kipsCount == 0) {
    printError(1, "");
  }
}

void updateScreen() {
  printf(CONSOLE_ESC(2J));
  printf(CONSOLE_MAGENTA CONSOLE_ESC(4m) "Kip Select V%d.%d.%d", VERSION_MAJOR, VERSION_MINOR, VERSION_MICRO);
  printf(CONSOLE_RESET " (+ To Exit Back To HB-Menu, - To Refresh Kip List)");
  printf(CONSOLE_ESC(45;68H) CONSOLE_MAGENTA "-By Sciguy429");
  printf(CONSOLE_ESC(4;1H) CONSOLE_RESET CONSOLE_ESC(4m) "Installed Kips:\n");
  for (int i = 0; i < kipsCount; i++) {
    printf(CONSOLE_RESET);
    if (kipsEnabled[i]) {
      printf(CONSOLE_GREEN);
    }
    else {
      printf(CONSOLE_RED);
    }
    if (kipSelected == i) {
      printf(CONSOLE_ESC(7m));
    }
    printf(" * %s\n", kips[i].c_str());
    printf(CONSOLE_RESET);
  }
}

void setKip(int kipId, bool enabled) {
  string name = kips[kipId];
  string start = "/atmosphere/";
  string end = "/atmosphere/";
  if (enabled) {
    start.append("kips_disabled/");
    end.append("kips/");
  }
  else {
    start.append("kips/");
    end.append("kips_disabled/");
  }
  start.append(name);
  end.append(name);
  if (rename(start.c_str(), end.c_str()) != 0) {
    printError(3, name);
  }
}

int main(int argc, char **argv)
{
  consoleInit(NULL);
  scanForKip();
  updateScreen();
  while(appletMainLoop() && run)
  {
    updateInputs();
    if (kDown & KEY_MINUS) {
      kipSelected = 0;
      scanForKip();
      updateScreen();
    }
    else if (kDown & KEY_DDOWN) {
      kipSelected++;
      if (kipSelected >= kipsCount) {
        kipSelected = kipsCount - 1;
      }
      else {
        updateScreen();
      }
    }
    else if (kDown & KEY_DUP) {
      kipSelected--;
      if (kipSelected <= -1) {
        kipSelected = 0;
      }
      else {
        updateScreen();
      }
    }
    else if (kDown & KEY_A) {
      kipsEnabled[kipSelected] = !kipsEnabled[kipSelected];
      setKip(kipSelected, kipsEnabled[kipSelected]);
      updateScreen();
    }
    consoleUpdate(NULL);
  }
  consoleExit(NULL);
  return 0;
}
